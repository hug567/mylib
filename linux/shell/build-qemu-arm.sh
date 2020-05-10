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

#
make clean
#
make mrproper
# 生成.config配置文件
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- vexpress_defconfig
# 编译内核
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi-
# 编译内核模块(.ko)
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- modules
# 编译dts文件(生成dtb文件)
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- dtbs
# qemu启动命令
echo -e "\n${YELLOW}Run kernel: ${GREEN}~/code/mylib/shell/qemu/qemu-run.sh${RESET}"
