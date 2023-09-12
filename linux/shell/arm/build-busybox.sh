#!/bin/bash

CPU_THREAD_NUM=$(cat /proc/cpuinfo | grep "processor" | wc -l)

if [ ! -f applets/busybox.mkll ]; then
    echo -e "${RED}Error: ${RESET}You are not in busybox root dir"
    exit
fi

make clean; make mrproper

# 生成.config配置文件
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- defconfig
sed -i "s/# CONFIG_STATIC is not set/CONFIG_STATIC=y/" .config

# 编译busybox
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j${CPU_THREAD_NUM}

# 安装
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- install
#make install -j3

# 制作rootfs
echo -e "\n${BLUE}Run kernel: ${GREEN}~/code/mylib/linux/shell/make-rootfs-arm.sh${RESET}"
