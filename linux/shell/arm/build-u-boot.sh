#!/bin/bash

make clean
make mrproper

make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_ca9x4_config
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j

# 拷贝u-boot文件至tftp根目录
sudo cp u-boot /var/lib/tftproot

# qemu启动命令
echo "Verify: qemu-system-arm -M vexpress-a9 -m 256M -kernel ./u-boot -nographic"
