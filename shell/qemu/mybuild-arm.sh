#!/bin/bash

make clean

make mrproper

make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- vexpress_defconfig

make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi-

echo -e "\nRun kernel: ~/code/mylib/shell/qemu/qemu-run.sh"
