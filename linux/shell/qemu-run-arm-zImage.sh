#!/bin/bash

# 环境准备：
# 创建tun网卡设备：sudo ip tuntap add dev tap0 mode tap
# 配置ip：sudo ifconfig tap0 192.168.0.100 netmask 255.255.255.0
# 删除tun网卡设备: sudo ip tuntap del dev tap0 mode tap

source $MYLIB/linux/shell/common.sh

ROOTFS=rootfs.qcow2
WORK_DIR=$HOME/code/linux
LINUX_DIR=$WORK_DIR/linux-4.18

# 清空屏幕
clear; clear

check_file_exist ${LINUX_DIR}/arch/arm/boot/zImage

# 创建虚拟网卡
VIR_TAP=$(ifconfig -a | grep tap)
if [ "x$VIR_TAP" = "x" ]; then
    log_info "Will create tap0 with ip 192.168.0.100"
    sudo ip tuntap add dev tap0 mode tap
    sudo ifconfig tap0 192.168.0.100 netmask 255.255.255.0
fi

# 串口重定向到标准输入输出
#    -serial stdio \

# 串口重定向到telnet
# 连接方式：telnet localhost 4321
#    -serial telnet:localhost:4321,server,nowait \

# 将qemu流量发送至主机串口设备
#    -chardev serial,id=s9,path=/dev/ttyS0 \

#    -serial pty \
#    -serial /dev/ttyS0 \
#    -serial stdio \
#    -chardev serial,id=s9,path=tty1 \
#    -serial vc:800x600 \
#    -semihosting \
qemu-system-arm \
    -M vexpress-a9 -m 512M -nographic \
    -kernel ${LINUX_DIR}/arch/arm/boot/zImage \
    -dtb ${LINUX_DIR}/arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
    -sd ${WORK_DIR}/${ROOTFS} \
    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,\
gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
    -append "root=/dev/mmcblk0 rw console=ttyAMA0"
