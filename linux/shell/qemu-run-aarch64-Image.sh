#!/bin/bash

# 清空屏幕
#clear; clear

if [ ! -f arch/arm64/boot/Image ]; then
    echo -e "${RED}Error: ${RESET}You are not in linux src root dir....."
    exit
fi

#qemu-system-aarch64 \
#    -M virt -m 512M -nographic \
#    -kernel arch/arm64/boot/Image \
#    -initrd ~/code/linux/rootfs.aarch64 \
#    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0"
#    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
#    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
#    -append "root=/dev/mmcblk0 rw console=ttyAMA0"
qemu-system-aarch64 \
    -M virt -cpu cortex-a57 -smp 1 -m 256 -nographic \
    -initrd ~/code/linux/rootfs.aarch64 \
    -kernel arch/arm64/boot/Image  \
    --append "console=ttyAMA0 rdinit=/linuxrc"
