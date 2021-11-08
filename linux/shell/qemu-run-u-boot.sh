#!/bin/bash

# 环境准备：
# 创建tun网卡设备：sudo ip tuntap add dev tap0 mode tap
# 配置ip：sudo ifconfig tap0 192.168.0.100 netmask 255.255.255.0
# 删除tun网卡设备: sudo ip tuntap del dev tap0 mode tap

# u-boot配置网络
#setenv ipaddr 192.168.0.103
#setenv gatewayip 192.168.0.1
#setenv netmask 255.255.255.0
#setenv serverip 192.168.0.100
#setenv bootargs 'root=/dev/mmcblk0 rw console=ttyAMA0'
#saveenv
# u-boot启动内核
#tftpboot 0x60003000 uImage
#bootm 0x60003000

source $MYLIB/linux/shell/common.sh

check_files_exist ./u-boot

# 创建虚拟网卡
VIR_TAP=$(ifconfig -a | grep tap)
if [ "x$VIR_TAP" = "x" ]; then
    log_info "Will create tap0 with ip 192.168.0.100"
    sudo ip tuntap add dev tap0 mode tap
    sudo ifconfig tap0 192.168.0.100 netmask 255.255.255.0
fi

QEMU="/home/hx/code/qemu/build-arm/arm-softmmu/qemu-system-arm"
#QEMU="qemu-system-arm"
${QEMU} \
    -M vexpress-a9 \
    -m 256M \
    -kernel ./u-boot \
    -nographic \
    -net nic \
    -net tap,ifname=tap0,script=no,downscript=no
