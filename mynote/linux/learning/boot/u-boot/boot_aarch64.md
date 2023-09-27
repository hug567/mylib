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

# 编辑dts：
qemu-system-aarch64 -machine virt -machine dumpdtb=qemu_arm64.dtb
dtc -I dtb -O dts -o qemu_arm64.dts qemu_arm64.dtb
#----- 注释中qemu_arm64.dts的pcie节点 ------------------------------#
/*
	pcie@10000000 {
		interrupt-map-mask = <0x1800 0x00 0x00 0x07>;
		interrupt-map = <0x00 0x00 0x00 0x01 0x8002 0x00 0x00 0x00 0x03 0x04 0x00 0x00 0x00 0x02 0x8002 0x00 0x00 0x00 0x04 0x04 0x00 0x00 0x00 0x03 0x8002 0x00 0x00 0x00 0x05 0x04 0x00 0x00 0x00 0x04 0x8002 0x00 0x00 0x00 0x06 0x04 0x800 0x00 0x00 0x01 0x8002 0x00 0x00 0x00 0x04 0x04 0x800 0x00 0x00 0x02 0x8002 0x00 0x00 0x00 0x05 0x04 0x800 0x00 0x00 0x03 0x8002 0x00 0x00 0x00 0x06 0x04 0x800 0x00 0x00 0x04 0x8002 0x00 0x00 0x00 0x03 0x04 0x1000 0x00 0x00 0x01 0x8002 0x00 0x00 0x00 0x05 0x04 0x1000 0x00 0x00 0x02 0x8002 0x00 0x00 0x00 0x06 0x04 0x1000 0x00 0x00 0x03 0x8002 0x00 0x00 0x00 0x03 0x04 0x1000 0x00 0x00 0x04 0x8002 0x00 0x00 0x00 0x04 0x04 0x1800 0x00 0x00 0x01 0x8002 0x00 0x00 0x00 0x06 0x04 0x1800 0x00 0x00 0x02 0x8002 0x00 0x00 0x00 0x03 0x04 0x1800 0x00 0x00 0x03 0x8002 0x00 0x00 0x00 0x04 0x04 0x1800 0x00 0x00 0x04 0x8002 0x00 0x00 0x00 0x05 0x04>;
		#interrupt-cells = <0x01>;
		ranges = <0x1000000 0x00 0x00 0x00 0x3eff0000 0x00 0x10000 0x2000000 0x00 0x10000000 0x00 0x10000000 0x00 0x2eff0000>;
		reg = <0x00 0x3f000000 0x00 0x1000000>;
		msi-parent = <0x8003>;
		dma-coherent;
		bus-range = <0x00 0x0f>;
		linux,pci-domain = <0x00>;
		#size-cells = <0x02>;
		#address-cells = <0x03>;
		device_type = "pci";
		compatible = "pci-host-ecam-generic";
	};
*/
#-----------------------------------------------------------------#
dtc -I dts -O dtb -o qemu_arm64.dtb qemu_arm64.dts
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
setenv serverip 192.168.0.1
setenv bootargs "rdinit=/linuxrc console=ttyAMA0"
saveenv
# u-boot下载镜像到内存：
tftpboot 0x40003000 Image
tftpboot 0x44000000 rootfs.ub
tftpboot 0x45000000 qemu_arm64.dtb
# u-boot启动linux：
booti 0x40003000 0x44000000 0x45000000
```
