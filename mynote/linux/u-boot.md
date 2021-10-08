## 1、主机配置：

```c
/* 主机创建tun/tap设备： */
sudo apt install uml-utilities bridge-utils              //安装依赖
sudo ip tuntap add dev tap0 mode tap                     //创建tap设备
sudo ifconfig tap0 192.168.0.100 netmask 255.255.255.0   //配置ip
sudo ip tuntap del dev tap0 mode tap                     //删除tap设备

/* 主机安装TFTP工具： */
sudo apt install tftp-hpa tftpd-hpa xinetd               //安装依赖
sudo vim /etc/default/tftpd-hpa                          //查看配置文件
TFTP_DIRECTORY="/var/lib/tftpboot"                       //拉取uImage目录
sudo /etc/init.d/tftpd-hpa restart                       //重启TFTP服务

/* 主机tftp测试： */
tftp localhost                                           //连接至本地
get <file>                                               //获取文件
status                                                   //查看状态
quit                                                     //推出tftp服务

// 修改网络配置：
//sudo vim /etc/network/interfaces
```

## 2、编译u-boot：

### 1）、下载u-boot源码：

```c
wget https://ftp.denx.de/pub/u-boot/u-boot-2014.01.tar.bz2
git clone https://github.com/u-boot/u-boot.git
git clone https://gitee.com/mirrors/u-boot.git
```

### 2)、编译u-boot：

```c
// 版本匹配：
arm-linux-gnueabi-gcc --version  // gcc 7.3.1 2018.05
git checkout -b v2018.05

mkdir build-vexpress_a9
cd build-vexpress_a9
    
/* 配置与编译： */
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_ca9x4_config
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j4

/* 启动验证u-boot： */
qemu-system-arm -M vexpress-a9 -m 256M -kernel ./u-boot -nographic -net nic -net tap,ifname=tap0,script=no,downscript=no

// u-boot配置网络：
setenv ipaddr 192.168.0.103
setenv ethaddr 00:04:9f:04:d2:35
setenv gatewayip 192.168.0.1
setenv netmask 255.255.255.0
setenv serverip 192.168.0.100
saveenv

// u-boot验证网络：
ping 192.168.0.100

// u-boot常用命令：
help / ?                    // 打印所有命令信息
help <cmd>                  // 打印指定命令帮助信息
setenv                      //设置环境变量
saveenv                     //保存环境变量
printenv                    //打印环境变量
```

```c
sudo apt install u-boot-tools    //安装mkimage工具

/* 编译内核通过u-boot引导： */
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- vexpress_defconfig
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- LOADADDR=0x60003000 uImage
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- modules    //编译内核模块
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- dtbs       //编译dts文件

sudo cp uImage /var/lib/tftproot
sudo cp u-boot /var/lib/tftproot
sudo cp vexpress-v2p-ca9.dtb /var/lib/tftproot
```

#### u-boot手动启动linux内核：

```c
qemu-system-arm -M vexpress-a9 \
    -kernel u-boot \
    -nographic \
    -initrd ~/code/linux/rootfs.img.gz \
    -net nic -net tap,ifname=tap0 \
    -m 512M

/* 手动启动uImage */
setenv etnaddr 11:22:33:44:55:66                         //设置板子的mac地址
setenv ipaddr 192.168.0.101                              //设置板子的IP地址
setenv serverip 192.168.0.100                            //设置提供内核下载的服务器IP地址
setenv gatewayip 192.168.0.1                             //设置网关
setenv netmask 255.255.255.0                             //设置子网掩码
setenv bootargs "root=/dev/mtdblock0 console=ttyAMA0"    //设置启动参数
saveenv                                                  //保存环境变量
tftp 60003000 uImage                                     //下载Image
tftp 60500000 vexpress-v2p-ca9.dtb                       //下载dtb
bootm 0x60003000 - 0x60500000                            //启动内核

setenv bootargs "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0 noapic"
```

## 3、常见错误：

### 1）、gcc版本问题：

```c
/home/hx/code/linux/u-boot/include/linux/compiler-gcc.h:93:1: fatal error: linux/compiler-gcc7.h: No such file or directory
 #include gcc_header(__GNUC__)
 ^~~~
compilation terminated.
```

* 原因：gcc版本超过4（注：\__GNUC__为gcc定义的主版本号宏）

* 解决：指定gcc版本为4

```c
diff --git a/include/linux/compiler-gcc.h b/include/linux/compiler-gcc.h
index 9896e547b9..c08ba74b26 100644
--- a/include/linux/compiler-gcc.h
+++ b/include/linux/compiler-gcc.h
@@ -90,4 +90,4 @@
 #define __gcc_header(x) #x
 #define _gcc_header(x) __gcc_header(linux/compiler-gcc##x.h)
 #define gcc_header(x) _gcc_header(x)
-#include gcc_header(__GNUC__)
+#include gcc_header(4)
```

### 2）、inline别名问题：

```c
board.c:66:6: error: ‘coloured_LED_init’ aliased to external symbol ‘__coloured_LED_init’
 void coloured_LED_init(void)
      ^~~~~~~~~~~~~~~~~
board.c:83:6: error: ‘blue_led_off’ aliased to external symbol ‘__blue_led_off’
 void blue_led_off(void) __attribute__((weak, alias("__blue_led_off")));
      ^~~~~~~~~~~~
board.c:81:6: error: ‘blue_led_on’ aliased to external symbol ‘__blue_led_on’
 void blue_led_on(void) __attribute__((weak, alias("__blue_led_on")));
      ^~~~~~~~~~~
board.c:79:6: error: ‘yellow_led_off’ aliased to external symbol ‘__yellow_led_off’
 void yellow_led_off(void) __attribute__((weak, alias("__yellow_led_off")));
      ^~~~~~~~~~~~~~
board.c:77:6: error: ‘yellow_led_on’ aliased to external symbol ‘__yellow_led_on’
 void yellow_led_on(void) __attribute__((weak, alias("__yellow_led_on")));
      ^~~~~~~~~~~~~
board.c:75:6: error: ‘green_led_off’ aliased to external symbol ‘__green_led_off’
 void green_led_off(void) __attribute__((weak, alias("__green_led_off")));
      ^~~~~~~~~~~~~
board.c:73:6: error: ‘green_led_on’ aliased to external symbol ‘__green_led_on’
 void green_led_on(void) __attribute__((weak, alias("__green_led_on")));
      ^~~~~~~~~~~~
board.c:71:6: error: ‘red_led_off’ aliased to external symbol ‘__red_led_off’
 void red_led_off(void) __attribute__((weak, alias("__red_led_off")));
      ^~~~~~~~~~~
board.c:69:6: error: ‘red_led_on’ aliased to external symbol ‘__red_led_on’
 void red_led_on(void) __attribute__((weak, alias("__red_led_on")));
      ^~~~~~~~~~
```

* 原因：inline函数不能添加弱符号别名

* 解决：指定弱符号别名的函数删除inline

```c
diff --git a/arch/arm/lib/board.c b/arch/arm/lib/board.c
index b770e25d87..ec4e478bfc 100644
--- a/arch/arm/lib/board.c
+++ b/arch/arm/lib/board.c
@@ -62,24 +62,24 @@ extern void dataflash_print_info(void);
  ************************************************************************
  * May be supplied by boards if desired
  */
-inline void __coloured_LED_init(void) {}
+void __coloured_LED_init(void) {}
 void coloured_LED_init(void)
        __attribute__((weak, alias("__coloured_LED_init")));
-inline void __red_led_on(void) {}
+void __red_led_on(void) {}
 void red_led_on(void) __attribute__((weak, alias("__red_led_on")));
-inline void __red_led_off(void) {}
+void __red_led_off(void) {}
 void red_led_off(void) __attribute__((weak, alias("__red_led_off")));
-inline void __green_led_on(void) {}
+void __green_led_on(void) {}
 void green_led_on(void) __attribute__((weak, alias("__green_led_on")));
-inline void __green_led_off(void) {}
+void __green_led_off(void) {}
 void green_led_off(void) __attribute__((weak, alias("__green_led_off")));
-inline void __yellow_led_on(void) {}
+void __yellow_led_on(void) {}
 void yellow_led_on(void) __attribute__((weak, alias("__yellow_led_on")));
-inline void __yellow_led_off(void) {}
+void __yellow_led_off(void) {}
 void yellow_led_off(void) __attribute__((weak, alias("__yellow_led_off")));
-inline void __blue_led_on(void) {}
+void __blue_led_on(void) {}
 void blue_led_on(void) __attribute__((weak, alias("__blue_led_on")));
-inline void __blue_led_off(void) {}
+void __blue_led_off(void) {}
 void blue_led_off(void) __attribute__((weak, alias("__blue_led_off")));
```

### 3）、符号重复定义：

```c
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_fdt.o: In function `__raw_writesb':
/home/hx/code/linux/u-boot/arch/arm/include/asm/io.h:80: multiple definition of `__raw_writesb'                                                     /home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_bootm.o:/home/hx/code/linux/u-boot/arch/arm/include/asm/io.h:80: first defined here
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_fdt.o: In function `fdt_valid':                                                             /home/hx/code/linux/u-boot/common/cmd_fdt.c:608: multiple definition of `__raw_writesw'
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_bootm.o:/home/hx/code/linux/u-boot/common/cmd_bootm.c:1461: first defined here
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_fdt.o: In function `fdt_valid':
/home/hx/code/linux/u-boot/common/cmd_fdt.c:608: multiple definition of `__raw_writesl'
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_bootm.o:/home/hx/code/linux/u-boot/common/cmd_bootm.c:1461: first defined here
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_fdt.o: In function `fdt_valid':
......
```

* 原因：头文件中inline函数声明为extern

* 解决：删除.h文件中inline函数的extern

```c
diff --git a/arch/arm/include/asm/io.h b/arch/arm/include/asm/io.h
index 6a1f05ac3e..0e64e7cf4f 100644
--- a/arch/arm/include/asm/io.h
+++ b/arch/arm/include/asm/io.h
@@ -75,7 +75,7 @@ static inline phys_addr_t virt_to_phys(void * vaddr)
 #define __arch_putw(v,a)               (*(volatile unsigned short *)(a) = (v))
 #define __arch_putl(v,a)               (*(volatile unsigned int *)(a) = (v))

-extern inline void __raw_writesb(unsigned long addr, const void *data,
+inline void __raw_writesb(unsigned long addr, const void *data,
                                 int bytelen)
 {
        uint8_t *buf = (uint8_t *)data;
@@ -83,7 +83,7 @@ extern inline void __raw_writesb(unsigned long addr, const void *data,
                __arch_putb(*buf++, addr);
 }

-extern inline void __raw_writesw(unsigned long addr, const void *data,
+inline void __raw_writesw(unsigned long addr, const void *data,
                                 int wordlen)
 {
        uint16_t *buf = (uint16_t *)data;
@@ -91,7 +91,7 @@ extern inline void __raw_writesw(unsigned long addr, const void *data,
                __arch_putw(*buf++, addr);
 }

-extern inline void __raw_writesl(unsigned long addr, const void *data,
+inline void __raw_writesl(unsigned long addr, const void *data,
                                 int longlen)
 {
        uint32_t *buf = (uint32_t *)data;
@@ -99,21 +99,21 @@ extern inline void __raw_writesl(unsigned long addr, const void *data,
                __arch_putl(*buf++, addr);
 }
......
```

















