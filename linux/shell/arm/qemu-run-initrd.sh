#!/bin/bash

# 环境准备：
# 创建tun网卡设备：sudo ip tuntap add dev tap0 mode tap
# 配置ip：sudo ifconfig tap0 192.168.0.100 netmask 255.255.255.0
# 删除tun网卡设备: sudo ip tuntap del dev tap0 mode tap

# 创建虚拟网卡
VIR_TAP=$(ifconfig -a | grep tap)
if [ "x$VIR_TAP" = "x" ]; then
    log_info "Will create tap0 with ip 192.168.0.100"
    sudo ip tuntap add dev tap0 mode tap
    sudo ifconfig tap0 192.168.0.100 netmask 255.255.255.0
fi

# 串口重定向到标准输入输出
#    -serial mon:stdio \

# 串口重定向到telnet
# 连接方式：telnet localhost 4321
#    -serial telnet:localhost:4321,server,nowait \

# 将qemu流量发送至主机串口设备
#    -chardev serial,id=s9,path=/dev/ttyS0 \

#QEMU="/home/hx/code/qemu/build-arm/arm-softmmu/qemu-system-arm"
qemu-system-arm \
    -M vexpress-a9 -m 512M -nographic \
    -kernel arch/arm/boot/zImage \
    -dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
    -initrd rootfs.cpio.gz \
    -append "rdinit=/linuxrc console=ttyAMA0"

#qemu-system-aarch64 \
#    -M virt -cpu cortex-a57 -smp 4 -m 256 -nographic \
#    -kernel ${image} \
#    -initrd ${rootfs} \
#    -device virtio-net-device,netdev=net0 \
#    -netdev tap,id=net0,script=no,downscript=no,ifname=tap0 \
#    --append "console=ttyAMA0 rdinit=/linuxrc"
