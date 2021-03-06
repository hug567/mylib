## 1、编译运行Linux内核

### 1.1、下载linaro arm-linux-gnueabi-gcc：

```c
/* 下载arm-linux-gnueabi-gcc并解压： */
https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/arm-linux-gnueabi/
/* 在~/.bashr和~/.zshrc中添加： */
export PATH="$HOME/tools/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabi/bin:$PATH"
source ~/.bashrc                                           //更新bash配置
source ~/.zshrc                                            //更新zsh配置
arm-none-linux-gnueabi-gcc --version                       //查看版本，验证路径设置正确
```

### 1.2、编译内核：

```c
sudo apt-get install gcc qemu libncurses5-dev openssl libssl-dev build-essential \
pkg-config libc6-dev bison flex libelf-dev                 //安装依赖
qemu-img --version                                         //查看qemu版本

cat /proc/version                                          //查看内核版本
//下载linux-4.15
wget https://mirror.bjtu.edu.cn/kernel/linux/kernel/v4.x/linux-4.15.tar.gz
tar -xvf linux-4.15.tar.gz                                 //解压linux内核
cd linux-4.15                                              //进入目录
make clean; make mrproper                                  //清除临时文件
/* 配置及编译： */
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_defconfig  //加载默认配置
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- menuconfig  //手动配置
General setup ---->
    [*] Configure standard kernel features (expert users)  --->
        [*]   Enable support for printk (NEW)
        [*] load all symbols for debugging/ksymoops
        [*]     Include all symbols in kallsyms
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-             //编译内核
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- modules     //编译内核模块
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- dtbs        //编译dts文件
find ./ -name "*Image*"                                         //查看Image文件
/* 无文件系统启动验证： */
qemu-system-arm -M virt -cpu cortex-a15 -m 256 \
    -kernel arch/arm/boot/zImage -nographic -append "console=ttyAMA0"
```

### 1.3、编译busybox：

```c
wget https://busybox.net/downloads/busybox-1.27.2.tar.bz2       //下载busybox
tar -xjvf busybox-1.27.2.tar.bz2                                //解压busybox
cd busybox-1.27.2                                               //进入目录
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- menuconfig  //手动配置
/* 选中以下配置： */
Busybox Settings  --->
    [*] Build BusyBox as a static binary (no shared libs)
Linux System Utilities ---->
    [*] mdev
    [*]   Support /etc/mdev.conf
    [*]     Support subdirs/symlinks
    [*]       Support regular expressions substitutions when renaming device
    [*]     Support command execution at device addition/removal
    [*]   Support loading of firmwares
Networking Utilities  --->
    [*] telnetd
    [*]   Support standalone telnetd (not inetd only)
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-             //编译
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- install     //安装
/* 所需内容在busybox-1.27.2/_install目录下 */
```

### 1.4、制作文件系统：

#### 1.4.1、制作init.d启动内核

```c
mkdir rootfs                                              //新建文件夹
cd rootfs                                                 //进入目录
sudo cp -rf ../busybox-1.27.2/_install/* ./               //复制文件
sudo mkdir proc sys dev etc etc/init.d                    //新建目录
sudo vim ./etc/init.d/rcS                                 //新建文件并写入
/*-------------------------------------------------------*/
#!/bin/sh
mount -t proc none /proc
mount -t sysfs none /sys
/sbin/mdev -s
sudo echo -e "#\!/bin/bash\nmount -t proc none /proc\nmount -t sysfs none /sys\n/sbin/mdev -s" ./etc/init.d/rcS
/*-------------------------------------------------------*/
sudo chmod a+x ./etc/init.d/rcS                           //添加可执行权限
find . | cpio -o --format=newc > ../rootfs.img            //制作文件系统
cd ..                                                     //返回上层目录
gzip -c rootfs.img > rootfs.img.gz                        //压缩文件系统
```
#### 1.4.2、制作从sd卡启动内核：
```c
mkdir rootfs
cd rootfs
sudo cp -r ../busybox-1.27.2/_install/* .
sudo mkdir -p proc sys tmp root dev etc/init.d usr/bin lib/modules
sudo vim etc/init.d/rcS
/*********************************************************************/
#!/bin/sh
mount -t tmpfs tmpfs /dev
mkdir -p /dev/pts
mount -t devpts devpts /dev/pts
mount -t proc proc /proc
mount -t sysfs sysfs /sys
/sbin/mdev -s
echo /sbin/mdev > /proc/sys/kernel/hotplug
telnetd
ifconfig eth0 192.168.0.101 netmask 255.255.255.0
/*********************************************************************/
sddo chmod a+x etc/init.d/rcS
sudo vim etc/passwd
/*********************************************************************/
root::0:0:root:/root:/bin/sh
/*********************************************************************/
cd dev
sudo mknod -m 666 tty1 c 4 1
sudo mknod -m 666 tty2 c 4 2
sudo mknod -m 666 tty3 c 4 3
sudo mknod -m 666 tty4 c 4 4
sudo mknod -m 666 console c 5 1
sudo mknod -m 666 null c 1 3
cd ../../
dd if=/dev/zero of=rootfs.ext3 bs=1M count=32
mkfs.ext3 rootfs.ext3
sudo mount -t ext3 rootfs.ext3 /mnt -o loop
sudo cp -r rootfs/* /mnt
sudo umount /mnt

qemu-system-arm \
    -M vexpress-a9 -m 512M -nographic \
    -kernel arch/arm/boot/zImage \
    -dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
    -sd ~/code/linux/rootfs.ext3 \
    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
    -append "root=/dev/mmcblk0 rw console=ttyAMA0"
```

### 1.5、运行kernel：

```c
qemu-system-arm \
    -M virt -smp 1 -m 256 \
    -kernel ./arch/arm/boot/zImage \
    -initrd ../rootfs.img.gz \
    -nographic \
    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0 noapic"

qemu命令：
-M <machine> : 机器型号
-cpu <model> : cpu模式
-smp n : cpu个数
-m 256 : 内存大小(MB)
-kernel <Image> : 内核镜像
-hda/-hdb/-hdd/-hdc <rootfs> : 虚拟机系统安装文件
-nographic : 不使用图形界面
-append : 内核命令行
	init : 文件系统启动后执行的linux的第一个进程
	root : 指定根文件系统设备
	console : 指定终端
```

### 1.6、更新至qemu 4.0：

```c
wget https://download.qemu.org/qemu-4.0.1.tar.xz          //下载qemu 4.0
sudo apt install python python3 zlib1g-dev libglib2.0-dev \
    libtool autoconf libpixman-1-dev flex bison           //安装依赖
./configure                                               //配置
make                                                      //编译
sudo make install                                         //安装
```

### 1.7、gdb调试linux内核：

```c
/* 启动内核： */
qemu-system-arm \
    -M virt -smp 1 -m 256 -nographic -s \
    -kernel arch/arm/boot/zImage \
    -initrd ../rootfs.img.gz \
    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0 noapic"

/* 启动gdb： */
arm-none-linux-gnueabi-gdb vmlinux
(gdb) target remote:1234
```

### 1.8、虚拟机挂载主机共享目录：

```shell
# 主机：
sudo apt install nfs-kernel-server             # 主机安装NFS Server
sudo vim /etc/exports                          # 设置共享目录
/home/hx/share *(rw,nohide,insecure,no_subtree_check,async,no_root_squash)
sudo exportfs -arv                             # 更新export配置
sudo  /etc/init.d/n                            # 重启NFS服务

# 虚拟机：
mkdir share
# 挂载主机目录：
mount -t nfs -o nolock,vers=4 192.168.0.100:/home/hx/share /share

# 内核开启NFS功能支持(vexpress_defconfig)：
File systems  --->
[*] Network File Systems  --->                                               CONFIG_NETWORK_FILESYSTEMS    已开
<*>   NFS client support                                                     CONFIG_NFS_FS                 已开
[*]         NFS client support for NFS version 3                             CONFIG_NFS_V3                 已开
[*]               NFS client support for the NFSv3 ACL protocol extension    CONFIG_NFS_V3_ACL             未开
[*]         NFS client support for NFS version 4 (EXPERIMENTAL)              CONFIG_NFS_V4                 未开
[*]               NFS client support for NFSv4.1 (DEVELOPER ONLY)            CONFIG_NFS_V4_1               未开
[*]         Root file system on NFS                                          CONFIG_ROOT_NFS               已开
[*] Networking support  --->                                                 CONFIG_NET                    已开
Networking options  --->
[*]   IP: kernel level autoconfiguration                                     CONFIG_IP_PNP                 已开
```

## 2、各版本gcc区别：

```c
1、arm-none-eabi-gcc：
	ARM architecture，no vendor，not target an operating system，complies with the ARM EABI，用于编译 ARM 架构的裸机系统，不适用编译 Linux 应用，不支持那些跟操作系统关系密切的函数，比如fork(2)，使用的是专用于嵌入式系统的C库newlib；

2、arm-none-linux-gnueabi-gcc：
	ARM architecture, no vendor, creates binaries that run on the Linux operating system, and uses the GNU EABI，主要用于编译ARM架构的u-boot、Linux内核、Linux应用等，实用glibc库；
```

## 3、编译u-boot：

```c
https://ftp.denx.de/pub/u-boot/                             //u-boot下载地址
wget https://ftp.denx.de/pub/u-boot/u-boot-2014.01.tar.bz2  //下载u-boot
tar -xjvf u-boot-2014.01.tar.bz2                            //解压u-boot
cd u-boot-2014.01                                           //进入目录
/* 配置与编译： */
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- vexpress_ca9x4_config
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi-
/* 启动验证u-boot： */
qemu-system-arm -M vexpress-a9 -m 256M -kernel ./u-boot -nographic

sudo apt install uml-utilities bridge-utils                 //安装依赖
sudo vim /etc/network/interfaces

/* ubuntu添加虚拟网卡： */
sudo apt install uml-utilities bridge-utils                 //安装依赖
sudo ip tuntap add name virt mode tap                       //添加虚拟网卡virt
sudo ifconfig virt 192.168.1.100 netmask 255.255.255.0      //配置虚拟网卡ip
ip a                                                        //查看配置是否生效
```

```c
/* 主机创建tun/tap设备： */
sudo ip tuntap add dev tap0 mode tap                     //创建tap设备
sudo ifconfig tap0 192.168.0.100 netmask 255.255.255.0   //配置ip
ip a                                                     //查看tap设备
sudo ip tuntap del dev tap0 mode tap                     //删除tap设备
/* 主机安装TFTP工具： */
sudo apt install tftp-hpa tftpd-hpa xinetd               //安装依赖
vim /etc/default/tftpd-hpa                               //查看配置文件
/var/lib/tftpboot                                        //拉取uImage目录
sudo /etc/init.d/tftpd-hpa restart                       //重启TFTP服务
/* tftp测试： */
tftp localhost / 192.168.0.100                           //连接至本地
get <file>                                               //获取文件
status                                                   //查看状态
quit                                                     //推出tftp服务

ifconfig eth0 192.168.0.101 netmask 255.255.255.0 dstaddr 192.168.0.100
ifconfig eth0 up
ifconfig

sudo apt install u-boot-tools    //安装mkimage工具
/* 编译内核通过u-boot引导： */
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- vexpress_defconfig
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- LOADADDR=0x60003000 uImage
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- modules    //编译内核模块
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- dtbs       //编译dts文件

/* 主机安装TFTP： */
sudo apt install tftp-hpa tftpd-hpa xinetd
sudo vim /etc/default/tftpd-hpa    //tftp配置文件
sudo /etc/init.d/tftpd-hpa restart    //更改tptp配置后重启服务

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

## 4、Linaro aarch64工具链编译linux内核:
```c
/* 下载工具链： */
https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/aarch64-linux-gnu/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz

/* 编译linux-4.18： */
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-

/* 编译busybox-1.27.1： */
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig  //手动配置
/* 选中以下配置： */
Busybox Settings  --->
    [*] Build BusyBox as a static binary (no shared libs)
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-             //编译
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- install     //安装

/* 制作rootfs: */
mkdir rootfs                                              //新建文件夹
cd rootfs                                                 //进入目录
sudo cp -rf ../busybox-1.27.2/_install/* ./               //复制文件
sudo mkdir -p proc sys dev etc/init.d                     //新建目录
sudo vim etc/init.d/rcS                                   //新建文件并写入
/*-------------------------------------------------------*/
#!/bin/sh
mount -t proc none /proc
mount -t sysfs none /sys
/sbin/mdev -s
/*-------------------------------------------------------*/
sudo chmod a+x etc/init.d/rcS                             //添加可执行权限
find . | cpio -o --format=newc > ../rootfs.img            //制作文件系统
cd ..                                                     //返回上层目录
gzip -c rootfs.img > rootfs.aarch64                       //压缩文件系统
sudo rm -rf rootfs rootfs.img

/* 启动内核： */
qemu-system-aarch64 \
    -M virt -cpu cortex-a57 -smp 1 -m 256 -nographic \
    -initrd ../rootfs.aarch64 \
    -kernel arch/arm64/boot/Image  \
    --append "console=ttyAMA0 rdinit=/linuxrc"
```

## 5、Linaro arm工具链编译linux内核：

```c
/* 下载工具链： */
http://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/arm-linux-gnueabi/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabi.tar.xz

/* 编译linux-4.18： */
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
/* 无文件系统启动验证： */
qemu-system-arm -M virt -cpu cortex-a15 -m 256 \
    -kernel arch/arm/boot/zImage -nographic -append "console=ttyAMA0"
/* 启动内核： */
qemu-system-arm \
    -M virt -smp 1 -m 256 -nographic \
    -kernel ./arch/arm/boot/zImage \
    -initrd ../rootfs.img.gz \
    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0"
```

## 6、使用交叉工具链及linux源码编译驱动ko

```c
/* Makefile: */
obj-m += test_char.o

KERNEL = ~/code/linux/linux-4.15
PWD = $(shell pwd)

modules:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- M=${PWD} -C ${KERNEL}  modules
	rm -rf modules.order Module.symvers .cache.mk .tmp_versions
	rm -rf .*.ko.cmd .*.o.cmd *.o *.mod.c

.PHONEY: clean
clean:
	rm -f *.o *.ko

/**************************************************************************/
/* 从host获取文件： */
ftpget -u username -p passwd 192.168.0.100 test_char.ko
/* 加载驱动： */
insmod test_char.ko
/* 卸载驱动： */
rmmod test_char.ko
```

