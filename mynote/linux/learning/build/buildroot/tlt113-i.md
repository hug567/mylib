# 1、TLT113-i编译镜像：

## 1）、需要的文件：

- LinuxSDK-v1.4.tar.gz (5.5G)
- dl.tar.gz (1.2G)

## 2）、制作docker镜像：

```bash
# 基础镜像：
ubuntu 18.04
# 安装工具：
sudo apt install texinfo pkg-config nfs-kernel-server samba ssh gcc autoconf patch wget texinfo zlib1g-dev dos2unix git gnupg flex bison gperf build-essential zip curl libc6-dev libncurses5-dev:i386 x11proto-core-dev libx11-dev:i386 libreadline6-dev:i386 libgl1-mesa-glx:i386 libgl1-mesa-dev g++-multilib tofrodos python-markdown libxml2-utils xsltproc zlib1g-dev:i386 gawk libssl-dev u-boot-tools:i386 mingw32
sudo apt install bc u-boot-tools kmod cpio liblzo2-2 busybox rsync
```

## 3）、在docker中编译：

```bash
# 加压文件：
mkdir test01
cd test01
tar -xvf ../LinuxSDK-v1.4.tar.gz
tar -xvf ../dl.tar.gz -C T113-i_v1.0/buildroot/buildroot-201902
# 编译：
cd T113-i_v1.0
source ./build/envsetup.sh
./build.sh
# 生成linux系统镜像：
./build.sh pack

# 编译出的镜像位置：
ls out/t113_i/tlt113-evm-nand/longan/
ls out/t113_i_linux_tlt113-evm-nand_uart0.img
ls out/t113_i_linux_tlt113-evm-nand-sdboot_uart0.img
```

- 单独编译部分组件：

```bash
# SPL和u-boot：
./build.sh bootloader
# linux内核：
./build.sh kernel
# 文件系统：
./build.sh buildroot_rootfs

# 编译完后打包：
./build.sh pack
```

## 4）、刷写到开发板中：

```bash
```

