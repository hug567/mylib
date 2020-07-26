#!/bin/bash

ROOTFS="${HOME}/code/rootfs/rootfs.img.gz"

if [ ! -f ./include/linux/kernel.h ]; then
    echo -e "${RED}Error: ${RESET}You are not in linux src root dir....."
    exit
fi

qemu-system-arm \
    -M virt  \
    -smp 1 \
    -m 256 \
    -kernel ./arch/arm/boot/zImage \
    -initrd ${ROOTFS} \
    -nographic \
    -net nic -net tap,ifname=tap0,script=no,downscript=no \
    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0 noapic"
#    -net nic,model=e1000 -net tap,ifname=tap0 \
