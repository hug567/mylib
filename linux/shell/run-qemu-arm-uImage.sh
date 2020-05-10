#!/bin/bash
echo "qemu to run linux"
qemu-system-arm \
    -M vexpress-a9  \
    -m 512M \
    -kernel /home/hx/code/linux/tftproot/u-boot \
    -initrd ../rootfs.img.gz \
    -nographic \
    -netdev user,id=tap0 -device e1000,netdev=tap0
    #-netdev nic,vlan=0 -netdev tap,vlan=0,ifname=tap0
#    -append "root=/dev/mtdblock0 rdinit=sbin/init console=ttyAMA0 noapic"
