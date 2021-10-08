#!/bin/bash

# 环境准备：
# 创建tun网卡设备：sudo ip tuntap add dev tap0 mode tap
# 配置ip：sudo ifconfig tap0 192.168.0.100 netmask 255.255.255.0
# 删除tun网卡设备: sudo ip tuntap del dev tap0 mode tap

source $MYLIB/linux/shell/common.sh

check_files_exist u-boot

# 创建虚拟网卡
VIR_TAP=$(ifconfig -a | grep tap)
if [ "x$VIR_TAP" = "x" ]; then
    log_info "Will create tap0 with ip 192.168.0.100"
    sudo ip tuntap add dev tap0 mode tap
    sudo ifconfig tap0 192.168.0.100 netmask 255.255.255.0
fi

#qemu-system-arm -M vexpress-a9 -m 256M -kernel ./u-boot -nographic
qemu-system-arm \
    -M vexpress-a9 -m 512M -nographic \
    -kernel ./u-boot
    -net nic,vlan=0 \
    -net tap,vlan=0,ifname=tap0

#    -serial mon:stdio

#    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
#    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,\
#gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
