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

ifconfig eth0 192.168.0.101 netmask 255.255.255.0 dstaddr 192.168.0.100
ifconfig eth0 up
ifconfig
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
qemu-system-arm -M vexpress-a9 -m 256M -kernel ./u-boot -nographic

sudo vim /etc/network/interfaces
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

* 原因：

  gcc版本超过4

* 解决：

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



















