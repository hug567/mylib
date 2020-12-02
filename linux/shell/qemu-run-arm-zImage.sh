#!/bin/bash

ROOTFS=rootfs.sd

# 清空屏幕
clear; clear

if [ ! -f arch/arm/boot/zImage ]; then
    echo -e "${RED}Error: ${RESET}You are not in linux src root dir....."
    exit
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
qemu-system-arm \
    -M vexpress-a9 -m 512M -nographic \
    -kernel arch/arm/boot/zImage \
    -dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
    -sd ~/code/linux/${ROOTFS} \
    -netdev tap,id=mynet,script=no,downscript=no,ifname=tap0 \
    -device virtio-net-device,netdev=mynet,mrg_rxbuf=off,csum=off,guest_csum=off,\
gso=off,guest_tso4=off,guest_tso6=off,guest_ecn=off,guest_ufo=off \
    -append "root=/dev/mmcblk0 rw console=ttyAMA0"
