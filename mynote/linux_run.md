## 1、编译运行Linux内核

### 1.1、下载arm-none-linux-gnueabi-gcc：

```c
/* 下载arm-none-linux-gnueabi-gcc并解压： */
wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-aarch64-linux.tar.bz2
/* 在~/.bashr和~/.zshrc中添加： */
export PATH="$HOME/tools/arm-2014.05/bin:$PATH"
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
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- vexpress_defconfig
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi-
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- modules    //编译内核模块
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- dtbs       //编译dts文件
find ./ -name "*Image*"                                     //查看Image文件
/* 无文件系统启动验证： */
qemu-system-arm -M virt -cpu cortex-a15 -m 256 \
    -kernel arch/arm/boot/zImage -nographic -append "console=ttyAMA0"
```

### 1.3、编译busybox：

```c
wget https://busybox.net/downloads/busybox-1.27.2.tar.bz2       //下载busybox
tar -xjvf busybox-1.27.2.tar.bz2                                //解压busybox
cd busybox-1.27.2                                               //进入目录
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- menuconfig  //手动配置
/* 进入第一行"Busybox Setting", 按Y选中"Build Busybox as a static binary" */
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi-             //编译
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- install     //安装
/* 所需内容在busybox-1.27.2/_install目录下 */
```

### 1.4、制作文件系统：

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

```c
/* 制作从sd卡启动的根文件系统： */
mkdir rootfs
cd rootfs
sudo cp -r ../busybox-1.27.2/_install/* .
sudo mkdir lib
sudo cp -r ~/tools/arm-2014.05/arm-none-linux-gnueabi/libc/lib/* lib/
mkdir dev
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
~/code/mylib/linux/shell/run-qemu-arm-sd.sh
```



### 1.5、运行kernel：

```c
qemu-system-arm \
    -M virt  \
    -smp 1 \
    -m 256 \
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
sudo apt-get install python python3 zlib1g-dev libglib2.0-dev \
    libtool autoconf libpixman-1-dev flex bison           //安装依赖
./configure                                               //配置
make                                                      //编译
sudo make install                                         //安装
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
sudo ip tuntap add name tap0 mode tap                    //创建tap设备
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
    -initrd /home/ubuntu/code/linux/rootfs.img.gz \
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