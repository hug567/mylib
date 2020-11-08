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

if [ ! -f ./include/linux/kernel.h ]; then
    echo -e "${RED}Error: ${RESET}You are not in linux src root dir....."
    exit
fi

# 删除编译生成文件
#make clean

# 删除编译生成文件与配置文件
#make mrproper

# 生成.config配置文件
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_defconfig

# 编译内核
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j${CPU_THREAD_NUM}

# 编译内核模块(.ko)
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- modules -j${CPU_THREAD_NUM}

# 编译dts文件(生成dtb文件)
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- dtbs -j${CPU_THREAD_NUM}

# qemu启动命令
echo -e "\n${GREEN}Run kernel: ${RESET}~/code/mylib/linux/shell/qemu-run-arm-zImage.sh"
