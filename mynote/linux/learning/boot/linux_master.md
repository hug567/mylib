# 编译运行linux主线：

- ubuntu 22.04

## 1、编译linux：

- 2024.06.03：6d69b6c12fce479fde7bc06f686212451688a102

```bash
sudo apt install gcc libncurses5-dev openssl libssl-dev build-essential pkg-config libc6-dev bison flex libelf-dev
sudo apt install libgmp-dev libmpc-dev

git clone https://github.com/torvalds/linux.git
cd linux

export PATH="/home/hx/tools/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabi/bin:$PATH"
mkdir build-vexpress
cd build-vexpress
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_defconfig
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j12
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- modules -j12
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- dtbs -j12
```

## 2、编译busybox：

- 2024.06.03：a6ce017a8a2db09c6f23aa6abf7ce21fd00c2fdf

```bash
git clone https://git.busybox.net/busybox
cd busybox

mkdir build-arm
cd build-arm
export PATH="/home/hx/tools/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabi/bin:$PATH"
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- menuconfig
#-----------------------------------------#
# 选中以下配置：
Settings  --->
    [*] Build static binary (no shared libs)
#-----------------------------------------#
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j12
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- install
```

## 3、制作rootfs：

```bash
```

## 4、qemu启动linux：

```bash
```

