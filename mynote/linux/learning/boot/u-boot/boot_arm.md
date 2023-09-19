# 1、编译u-boot：

```bash
# u-boot v2019.01
# 下载源码：
wget https://ftp.denx.de/pub/u-boot/u-boot-2019.01.tar.bz2
git clone https://github.com/u-boot/u-boot.git
git clone https://gitee.com/mirrors/u-boot.git
# 编译：
mkdir build-arm
cd build-arm
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_ca9x4_config
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j3
# 验证可启动：
qemu-system-arm -M vexpress-a9 -m 256M -kernel ./u-boot -nographic
```

# 2、编译busybox：

## 2.1、编译：

```bash
# busybox-1.35.0
# 下载源码：
wget https://busybox.net/downloads/busybox-1.35.0.tar.bz2
# 编译：
mkdir build-arm
cd build-arm
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- defconfig
sed -i "s/# CONFIG_STATIC is not set/CONFIG_STATIC=y/" .config
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- oldconfig
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j3
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- install
```

## 2.2、制作rootfs：

```bash
mkdir rootfs
cd rootfs
cp -rf ../_install/* .
mkdir -p proc sys tmp dev/pts etc/init.d usr/bin lib/modules
touch etc/init.d/rcS
chmod +x etc/init.d/rcS
vim etc/init.d/rcS
#-----------------------------------------------------#
#!/bin/sh
mount -t proc none /proc
mount -t sysfs none /sys
/sbin/mdev -s
mount -t devpts devpts /dev/pts
telnetd
ifconfig eth0 192.168.0.100 netmask 255.255.255.0
#-----------------------------------------------------#
touch etc/passwd
vim etc/passwd
#-----------------------------------------------------#
root::0:0:root:/root:/bin/sh
#-----------------------------------------------------#
find . | cpio -o --format=newc > ../rootfs.cpio
cd ..
gzip -c rootfs.cpio > rootfs.cpio.gz
mkimage -A arm -O linux -T ramdisk -C none -a 0x62000000 -e 0x62000040 -d rootfs.cpio.gz rootfs.ub
```

# 3、编译linux：

```bash
# linux-5.10
mkdir build-arm
cd build-arm
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_defconfig
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j3
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- dtbs
mkimage -A arm -O linux -T kernel -C none -a 0x60003000 -e 0x60003040 -d arch/arm/boot/zImage uImage
```

# 4、启动：

- 搭建tftp server：[tftp.md](../../../man_cmd/net/tftp.md)

```bash
# qemu-system-arm 7.0.0
# host创建tap0：
sudo apt install uml-utilities bridge-utils
sudo ip tuntap add dev tap0 mode tap
sudo ifconfig tap0 192.168.0.1 netmask 255.255.255.0
sudo ip tuntap del dev tap0 mode tap
# u-boot启动linux：
qemu-system-arm -M vexpress-a9 -m 256M -kernel ./u-boot -nographic -net nic -net tap,ifname=tap0,script=no,downscript=no
# u-boot设置参数：
setenv ipaddr 192.168.0.10
setenv ethaddr 00:04:9f:04:d2:35
setenv gatewayip 192.168.0.1
setenv netmask 255.255.255.0
setenv serverip 192.168.0.1
setenv bootargs "rdinit=/linuxrc console=ttyAMA0"
saveenv
# u-boot下载镜像到内存：
tftpboot 0x60003000 uImage
tftpboot 0x61000000 vexpress-v2p-ca9.dtb
tftpboot 0x62000000 rootfs.ub
# u-boot启动linux：
bootm 0x60003000 0x62000000 0x61000000
```

