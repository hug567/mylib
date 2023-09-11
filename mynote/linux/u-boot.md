## 1、主机配置：

```bash
# 机创建tun/tap设备：
sudo apt install uml-utilities bridge-utils              # 安装依赖
sudo ip tuntap add dev tap0 mode tap                     # 创建tap设备
sudo ifconfig tap0 192.168.1.10 netmask 255.255.255.0    # 配置ip
sudo ip tuntap del dev tap0 mode tap                     # 删除tap设备

# 主机安装TFTP工具：
sudo apt install tftp-hpa tftpd-hpa xinetd               # 安装依赖
sudo /etc/init.d/tftpd-hpa start                         # 启动服务
sudo systemctl start tftpd-hpa.service                   # 启动服务

# 默认目录：/srv/tfpt
sudo vim /etc/default/tftpd-hpa                          # 查看配置文件
#--------------------------------------------------#
TFTP_DIRECTORY="/var/lib/tftpboot"                       # 拉取uImage目录
#--------------------------------------------------#
sudo /etc/init.d/tftpd-hpa restart                       # 重启TFTP服务

# 主机tftp测试：
tftp localhost                                           # 连接至本地
get <file>                                               # 获取文件
status                                                   # 查看状态
quit                                                     # 退出tftp服务

# 修改网络配置：
#sudo vim /etc/network/interfaces
```

## 2、编译u-boot：

### 2.1、下载u-boot源码：

```c
wget https://ftp.denx.de/pub/u-boot/u-boot-2014.01.tar.bz2
git clone https://github.com/u-boot/u-boot.git
git clone https://gitee.com/mirrors/u-boot.git
```

### 2.2、编译u-boot：

#### 2.2.1、arm：

- 已验证可编译：v2018.05、v2019.01

```bash
# 版本匹配：
arm-linux-gnueabi-gcc --version  # gcc 7.3.1 2018.05

cd u-boot
git checkout -b v2018.05
make clean; make mrproper; make distclean    # 清除编译临时文件

# 配置与编译arm版：
mkdir build-vexpress_a9
cd build-vexpress_a9
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_ca9x4_config
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j4

# 创建tap0：
sudo ip tuntap add dev tap0 mode tap
sudo ifconfig tap0 192.168.0.1 netmask 255.255.255.0

# 启动验证u-boot：
qemu-system-arm -M vexpress-a9 -m 256M -kernel ./u-boot -nographic -net nic -net tap,ifname=tap0,script=no,downscript=no
````
#### 2.2.2、aarch64：
````bash
# 编译aarch64版：
cd u-boot
make clean; make mrproper; make distclean
mkdir build-aarch64
cd build-aarch64
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- qemu_arm64_defconfig
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- -j3

# 启动验证：
qemu-system-aarch64 -M virt -cpu cortex-a57 -m 1024M -kernel ./u-boot -nographic -net nic -net tap,ifname=tap0,script=no,downscript=no
```
### 2.3、启动：

#### 2.3.1、常用命令：

```bash
# u-boot设置参数：
setenv ipaddr 192.168.1.13
setenv ethaddr 00:04:9f:04:d2:35
setenv gatewayip 192.168.1.1
setenv netmask 255.255.255.0
setenv serverip 192.168.1.10
setenv bootargs "root=/dev/mmcblk0 rw console=ttyAMA0"
saveenv

# u-boot验证网络：
ping 192.168.1.10           # host 192.168.1.10 is alive

# u-boot常用命令：
help / ?                    # 打印所有命令信息
help <cmd>                  # 打印指定命令帮助信息
setenv                      # 设置环境变量
saveenv                     # 保存环境变量
printenv                    # 打印环境变量
```

#### 2.3.2、制作linux镜像：

```c
sudo apt install u-boot-tools    //安装mkimage工具

// 制作linux uImage:
mkimage -A arm -O linux -T kernel -C none -a 0x60003000 -e 0x60003040 -d arch/arm/boot/zImage uImage
mkimage -A arm64 -O linux -T kernel -C none -a 0x60003000 -e 0x60003040 -d arch/arm64/boot/Image.gz uImage

// 拷贝镜像至tftp目录:
sudo cp uImage /var/lib/tftproot
sudo cp vexpress-v2p-ca9.dtb /var/lib/tftproot
```

#### 2.3.3、手动启动linux内核：

```c
/* 启动u-boot: */
qemu-system-arm -M vexpress-a9 -m 256M -kernel ./u-boot -nographic -net nic -net tap,ifname=tap0,script=no,downscript=no
qemu-system-aarch64 -M virt -m 1024M -cpu cortex-a57 -kernel ./u-boot -nographic -net nic -net tap,ifname=tap0,script=no,downscript=no

/* 下载并启动镜像： */
tftp 0x60003000 uImage
tftp 0x60500000 vexpress-v2p-ca9.dtb
bootm 0x60003000 - 0x60500000

// 下载aarch64镜像：
tftp 0x60003000 uImage
tftp 0x61000000 qemu-arm64.dtb
bootm 0x60003000 - 0x61000000               // 需计算各组件大小，保证不互相覆盖
```

## 3、u-boot 64字节头：

```bash
#define IH_MAGIC        0x27051956      /* Image Magic Number           */
#define IH_NMLEN                32      /* Image Name Length            */

struct legacy_img_hdr {
        uint32_t        ih_magic;       /* Image Header Magic Number    */
        uint32_t        ih_hcrc;        /* Image Header CRC Checksum    */
        uint32_t        ih_time;        /* Image Creation Timestamp     */
        uint32_t        ih_size;        /* Image Data Size              */
        uint32_t        ih_load;        /* Data  Load  Address          */
        uint32_t        ih_ep;          /* Entry Point Address          */
        uint32_t        ih_dcrc;        /* Image Data CRC Checksum      */
        uint8_t         ih_os;          /* Operating System             */
        uint8_t         ih_arch;        /* CPU architecture             */
        uint8_t         ih_type;        /* Image Type                   */
        uint8_t         ih_comp;        /* Compression Type             */
        uint8_t         ih_name[IH_NMLEN];      /* Image Name           */
};

=> md 0x60003000
60003000: 56190527 ca60a28f ac4a6b63 8667aa00  '..V..`.ckJ...g.
60003010: 00300060 40300060 502d62aa 00021605  `.0.`.0@.b-P....
60003020: 00000000 00000000 00000000 00000000  ................
60003030: 00000000 00000000 00000000 00000000  ................

ih_os   = 0x05 : linux
ih_arch = 0x16 : arm64
ih_type = 0x02 : kernel
ih_comp = 0x00 : none ?
          0x02 : gzip
```

## 4、u-boot内存分布：

```c
CONFIG_ENV_ADDR=0x04000000  // 环境变量存储地址
CONFIG_ENV_OFFSET 
CONFIG_ENV_SIZE=0x40000
CONFIG_ENV_SECT_SIZE=0x40000
CONFIG_SYS_LOAD_ADDR=0x40200000  //
CONFIG_DEBUG_UART_BASE=0x9000000
```

## 5、常见错误：

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

### 4）、设置mac地址失败

* 原因：未使能CONFIG_ENV_OVERWRITE
* 解决：在config文件中使能CONFIG_ENV_OVERWRITE=y后，重新编译
```bash
=> setenv ethaddr 00:04:9f:04:d2:35
## Error: Can't overwrite "ethaddr"
## Error inserting "ethaddr" variable, errno=1
```

## 6、u-boot传递给kernel的信息：

- 内核地址：
- initrd地址：
- dtb地址：x0
- cmdline：

## 7、常用命令：

### 1)、常用：

```bash
help / ?
help <cmd>
printenv
# 查看板子硬件信息
bdinfo
# 查看uImage信息
iminfo  0x60003000
# 查看内存二进制值
md 0x60003000
```

### 2）、mmc：

```bash
# 查看mmc设备信息
mmc info
```

### 3）、fat：

```bash
# 查看指定设备的fat文件系统信息
fatinfo mmc 0
# 查看指定fat文件系统中的文件
fatls mmc 0
fatls mmc 0 <dir>
# 查看fat文件系统类型
fstype mmc 0
# 读取文件到内存指定地址
fatload mmc 0 0x00000000 /success/BOOT.BIN
# 把内存中文件写入mmc设备
fatwrite mmc 0 00000000 image.ub 0x90caa8
```










