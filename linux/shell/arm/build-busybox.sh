#!/bin/bash
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
PURPLE="\033[35m"
SKYBLUE="\033[36m"
WHITE="\033[37m"
RESET="\033[0m"

CPU_THREAD_NUM=`cat /proc/cpuinfo |grep "processor"|wc -l`

# 清空屏幕
clear; clear

if [ ! -f applets/busybox.mkll ]; then
    echo -e "${RED}Error: ${RESET}You are not in busybox root dir"
    exit
fi

make clean; make mrproper

# 生成.config配置文件
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- defconfig
sed -i "s/# CONFIG_STATIC is not set/CONFIG_STATIC=y/" .config

# 编译busybox
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j${CPU_THREAD_NUM}

# 安装
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- install

# 制作rootfs
echo -e "\n${BLUE}Run kernel: ${GREEN}~/code/mylib/linux/shell/make-rootfs-arm.sh${RESET}"
