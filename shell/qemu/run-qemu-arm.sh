#!/bin/bash
echo "qemu to run linux"
qemu-system-arm \
    -M virt  \
    -smp 1 \
    -m 256 \
    -kernel ./arch/arm/boot/zImage \
    -initrd ../rootfs.img.gz \
    -nographic \
    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0 noapic"
