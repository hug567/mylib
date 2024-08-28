# 编译运行linux主线：

- ubuntu 22.04

## 1、编译linux：

- 2024.06.03：6d69b6c12fce479fde7bc06f686212451688a102
- arm最新交叉编译工具链：https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

```bash
sudo apt install gcc libncurses5-dev openssl libssl-dev build-essential pkg-config libc6-dev bison flex libelf-dev
sudo apt install libgmp-dev libmpc-dev

git clone https://github.com/torvalds/linux.git
cd linux

export PATH="$HOME/tools/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-linux-gnueabihf/bin:$PATH"
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- vexpress_defconfig
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- -j12
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- modules -j12
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- dtbs -j12
```

## 2、编译busybox：

- 2024.06.03：a6ce017a8a2db09c6f23aa6abf7ce21fd00c2fdf

```bash
git clone https://git.busybox.net/busybox
cd busybox

mkdir build-arm
cd build-arm
export PATH="$HOME/tools/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-linux-gnueabihf/bin:$PATH"
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- menuconfig
#-----------------------------------------#
# 选中以下配置：
Settings  --->
    [*] Build static binary (no shared libs)
#-----------------------------------------#
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- -j12
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- install
```

## 3、制作rootfs：

```bash
mkdir rootfs                                              # 新建文件夹
cd rootfs                                                 # 进入目录
cp -r ../busybox/build-arm/_install/* .                   # 复制文件
sudo mkdir -p proc sys dev etc etc/init.d                 # 新建目录
sudo vim ./etc/init.d/rcS                                 # 新建文件并写入
# ------------------------------------------------------- #
#!/bin/sh
mount -t proc none /proc
mount -t sysfs none /sys
/sbin/mdev -s
# ------------------------------------------------------- #
chmod a+x ./etc/init.d/rcS                                # 添加可执行权限
find . | cpio -o --format=newc > ../rootfs.cpio           # 制作文件系统
cd ..                                                     # 返回上层目录
gzip -c rootfs.cpio > rootfs.gz                           # 压缩文件系统
```

## 4、qemu启动linux：

```bash
cd linux/build-vexpress
qemu-system-arm \
    -M virt -smp 1 -m 256 \
    -kernel ./arch/arm/boot/zImage \
    -initrd ../../rootfs.gz \
    -nographic \
    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0 noapic"

# 退出qmeu: Ctrl+A, X
```

