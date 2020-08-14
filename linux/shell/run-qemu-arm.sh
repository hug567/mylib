#!/bin/bash

ROOTFS="${HOME}/code/linux/rootfs.img.gz"

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
    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0 noapic"
#    -net nic,model=e1000 -net tap,ifname=tap0 \
