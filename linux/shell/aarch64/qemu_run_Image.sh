#!/bin/bash

CUR_SOURCE_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd $CUR_SOURCE_DIR/../../..; pwd)
source $MYLIB/linux/shell/common.sh

#qemu-system-aarch64 \
#    -M virt -m 512M -nographic \
#    -kernel arch/arm64/boot/Image \
#    -initrd ~/code/linux/rootfs.aarch64 \
#    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0"
#    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
#    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
#    -append "root=/dev/mmcblk0 rw console=ttyAMA0"

function usage() {
    log_info "$0          running linux by qemu-system-aarch64"
    log_info "$0 -m       make rootfs before running"
}

function make_rootfs() {
    $MYLIB/linux/shell/aarch64/make_rootfs.sh $HOME/code/linux-code/busybox-1.32/build-arm64/_install
}

function qemu_run() {
    local image="arch/arm64/boot/Image"
    local rootfs="rootfs.cpio.gz"

    check_files_exist $image $rootfs

    create_net_tun_dev

    qemu-system-aarch64 \
        -M virt -cpu cortex-a57 -smp 4 -m 256 -nographic \
        -kernel ${image} \
        -initrd ${rootfs} \
        -device virtio-net-device,netdev=net0 \
        -netdev tap,id=net0,script=no,downscript=no,ifname=tap0 \
        --append "console=ttyAMA0 rdinit=/linuxrc"
}

function main() {
    local update_rootfs=

    if [ $# -gt 1 ]; then
        usage
        exit -1
    fi

    set -- $(getopt mh "$@")
    while [ -n "$1" ]; do
        case $1 in
            -m) update_rootfs=1; shift;;
            -h) usage; exit 1;;
        esac
        shift
    done

    if [ $update_rootfs -eq 1 ]; then
        make_rootfs
    fi
    qemu_run
}

main $*
