#!/bin/bash

make clean
make mrproper

mkdir build-arm
cd build-arm
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_ca9x4_config
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j3

# qemu启动命令
echo "Verify: qemu-system-arm -M vexpress-a9 -m 256M -kernel ./u-boot -nographic"
