#!/bin/bash

# 环境准备：
# 创建tun网卡设备：
#   sudo ip tuntap add dev tap0 mode tap
# 配置ip：
#   sudo ifconfig tap0 192.168.0.100 netmask 255.255.255.0
# 删除tun网卡设备:
#   sudo ip tuntap del dev tap0 mode tap

CUR_SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${CUR_SCRIPT_DIR}/../../../; pwd)
source ${MYLIB}/linux/shell/common.sh

check_files_exist arch/arm64/boot/Image

qemu-system-aarch64  \
    -M raspi3b -m 1024 -nographic \
    -initrd rootfs.cpio \
    -kernel arch/arm64/boot/Image \
    -dtb arch/arm64/boot/dts/broadcom/bcm2710-rpi-3-b.dtb \
    --append "rw earlycon=pl011,0x3f201000 console=ttyAMA0 loglevel=8 \
rdinit=/linuxrc fsck.repair=yes net.ifnames=0 rootwait dwc_otg.fiq_fsm_enable=0"

#    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
#    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,\
#gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
#
