#!/bin/bash

# 清空屏幕
clear; clear

if [ ! -f ./include/linux/kernel.h ]; then
    echo -e "${RED}Error: ${RESET}You are not in linux src root dir....."
    exit
fi

qemu-system-arm \
    -M vexpress-a9 -m 512M -nographic \
    -kernel arch/arm/boot/zImage \
    -dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
    -sd ~/code/linux/rootfs.sd \
    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
    -append "root=/dev/mmcblk0 rw console=ttyAMA0"
