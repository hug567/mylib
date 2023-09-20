# 1、编译u-boot：

```bash
# u-boot v2019.01
# 下载源码：
wget https://ftp.denx.de/pub/u-boot/u-boot-2019.01.tar.bz2
git clone https://github.com/u-boot/u-boot.git
git clone https://gitee.com/mirrors/u-boot.git
# 编译：
mkdir build-aarch64
cd build-aarch64
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- qemu_arm64_defconfig
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- -j3
# 验证可启动：
qemu-system-aarch64 -M virt -cpu cortex-a57 -m 256M -kernel ./u-boot -nographic
```

# 2、编译busybox：

## 2.1、编译：

```bash
# busybox-1.35.0
# 下载源码：
wget https://busybox.net/downloads/busybox-1.35.0.tar.bz2
# 编译：
mkdir build-aarch64
cd build-aarch64
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig
sed -i "s/# CONFIG_STATIC is not set/CONFIG_STATIC=y/" .config
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- oldconfig
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j3
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- install
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
mkimage -A arm -O linux -T ramdisk -C none -a 0x42000000 -e 0x42000040 -d rootfs.cpio.gz rootfs.ub
```

# 3、编译linux：

```bash
# linux-5.10
mkdir build-aarch64
cd build-aarch64
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j3
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- dtbs
mkimage -A arm -O linux -T kernel -C none -a 0x40003000 -e 0x40003040 -d arch/arm64/boot/Image.gz uImage
```

# 4、启动：

- 搭建tftp server：../../../man_cmd/net/tftp.md

```bash
# qemu-system-arm 7.0.0
# host创建tap0：
sudo apt install uml-utilities bridge-utils
sudo ip tuntap add dev tap0 mode tap
sudo ifconfig tap0 192.168.0.1 netmask 255.255.255.0
sudo ip tuntap del dev tap0 mode tap
# u-boot启动linux：
qemu-system-aarch64 -M virt -cpu cortex-a57 -m 256M -kernel ./u-boot -nographic -device virtio-net-device,netdev=net0 -netdev tap,id=net0,script=no,downscript=no,ifname=tap0
# u-boot设置参数：
setenv ipaddr 192.168.0.10
setenv gatewayip 192.168.0.1
setenv netmask 255.255.255.0
setenv serverip 192.168.0.1
setenv bootargs "rdinit=/linuxrc console=ttyAMA0"
saveenv
# u-boot下载镜像到内存：
tftpboot 0x40003000 uImage
tftpboot 0x41000000 vexpress-v2f-1xv7-ca53x2.dtb
tftpboot 0x41000000 foundation-v8.dtb
tftpboot 0x42000000 rootfs.ub
# u-boot启动linux：
bootm 0x40003000 0x42000000 0x41000000
```

