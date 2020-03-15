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

make clean

make mrproper

make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- vexpress_defconfig

make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi-

echo -e "\n${YELLOW}Run kernel: ${GREEN}~/code/mylib/shell/qemu/qemu-run.sh${RESET}"
