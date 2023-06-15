#!/bin/bash

START_TIME=$(date +%s)
CUR_SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${CUR_SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/yocto/common.sh

usage() {
    log_info "$0 <minimal/full>  using qemu run kernel"
}

#qemu-system-aarch64 \
#    -device virtio-net-device,netdev=net0,mac=52:54:00:12:34:02 \
#    -netdev tap,id=net0,ifname=tap0,script=no,downscript=no \
#    -object rng-random,filename=/dev/urandom,id=rng0 \
#    -device virtio-rng-pci,rng=rng0 \
#    -drive id=disk0,file=core-image-minimal-qemuarm64-20230408154253.rootfs.ext4,if=none,format=raw \
#    -device virtio-blk-device,drive=disk0 \
#    -device qemu-xhci \
#    -device usb-tablet \
#    -device usb-kbd  \
#    -machine virt -cpu cortex-a57 -smp 4 -m 256 -serial mon:vc -serial null \
#    -display sdl,show-cursor=on \
#    -device virtio-gpu-pci \
#    -kernel Image--5.15.32+git0+63e25b5717_387a676543-r0-qemuarm64-20230408154253.bin \
#    -append 'root=/dev/vda rw mem=256M ip=192.168.7.2::192.168.7.1:255.255.255.0::eth0:off:8.8.8.8'

#        -device virtio-net-pci,netdev=net0,mac=52:54:00:12:34:02 \
#        -netdev user,id=net0,hostfwd=tcp::2222-:22 \

run_kernel() {
    local image=$1
    check_files_exist ./tmp/deploy/images/qemuarm64/Image-qemuarm64.bin

    cd tmp/deploy/images/qemuarm64

    local disk1="./disk1.img"
    local dev_disk1=""
    if [ -f $disk1 ]; then
        dev_disk1="
        -device virtio-blk-device,drive=disk1 \
        -drive id=disk1,file=./disk1.img,if=none,format=raw \
        "
    fi

    qemu-system-aarch64 \
        -M virt -cpu cortex-a57 -smp 4 -m 256 -nographic \
        -kernel Image-qemuarm64.bin \
        ${dev_disk1} \
        -device virtio-blk-device,drive=disk0 \
        -drive id=disk0,file=${image},if=none,format=raw \
        -device virtio-net-device,netdev=net0,mac=52:54:00:12:34:02 \
        -netdev tap,id=net0,script=no,downscript=no,ifname=tap0 \
        -object rng-random,filename=/dev/urandom,id=rng0 \
        -device virtio-rng-pci,rng=rng0 \
        -device qemu-xhci \
        -device usb-tablet \
        -device usb-kbd  \
        -device virtio-gpu-pci \
        --append "root=/dev/vda rw mem=256M ip=192.168.0.101::192.168.0.1:255.255.255.0::eth0:off:8.8.8.8"
}

main() {
    if [ "$#" != "1" ]; then
        usage
        exit 1
    fi
    local image=$1
    case $image in
        minimal)
            run_kernel core-image-minimal-qemuarm64.ext4
            ;;
        full)
            run_kernel core-image-full-cmdline-qemuarm64.ext4
            ;;
        *)
            usage
            exit 2
    esac
}

main $*
