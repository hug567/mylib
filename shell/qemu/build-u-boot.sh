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
# 生成配置文件
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- vexpress_ca9x4_config
# 编译文件
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi-
# qemu启动命令
echo -e "\n${YELLOW}Verify: ${GREEN}qemu-system-arm -M vexpress-a9 -m 256M -kernel ./u-boot -nographic${RESET}"
