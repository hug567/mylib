#!/bin/bash

CUR_SOURCE_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd $CUR_SOURCE_DIR/../../..; pwd)
source $MYLIB/linux/shell/common.sh

IMAGE="arch/arm64/boot/Image"
ROOTFS="rootfs.gzip"
DTB=""

check_files_exist $IMAGE $ROOTFS
create_net_tun_dev

#qemu-system-aarch64 \
#    -M virt -m 512M -nographic \
#    -kernel arch/arm64/boot/Image \
#    -initrd ~/code/linux/rootfs.aarch64 \
#    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0"
#    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
#    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
#    -append "root=/dev/mmcblk0 rw console=ttyAMA0"
qemu-system-aarch64 \
    -M virt -cpu cortex-a57 -smp 4 -m 256 -nographic \
    -kernel ${IMAGE} \
    -initrd ${ROOTFS} \
    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,\
gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
    --append "console=ttyAMA0 rdinit=/linuxrc"
