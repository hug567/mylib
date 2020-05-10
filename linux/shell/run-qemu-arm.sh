#!/bin/bash
echo "qemu to run linux"

WORK_DIR="${HOME}/code/linux"
LINUX_DIR="${WORK_DIR}/linux-4.15"
IMAGE="${LINUX_DIR}/arch/arm/boot/zImage"
ROOTFS="${WORK_DIR}/rootfs.img.gz"


qemu-system-arm \
    -M virt  \
    -smp 1 \
    -m 256 \
    -kernel ${IMAGE} \
    -initrd ${ROOTFS} \
    -nographic \
    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0 noapic"
