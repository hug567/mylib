#!/bin/bash
echo "qemu to run linux"

WORK_DIR="${HOME}/code/linux"
LINUX_DIR="${WORK_DIR}/linux-4.15"
IMAGE="${LINUX_DIR}/arch/arm/boot/zImage"
DTB="${LINUX_DIR}/arch/arm/boot/dts/vexpress-v2p-ca9.dtb"
ROOTFS="${WORK_DIR}/rootfs.ext3"

qemu-system-arm \
    -M vexpress-a9  \
    -m 512M \
    -kernel ${IMAGE} \
    -dtb ${DTB}\
    -sd ${ROOTFS} \
    -nographic \
    -append "root=/dev/mmcblk0 rw console=ttyAMA0"
