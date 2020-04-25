#!/bin/bash

MYLIB="$(pwd)/../.."
LINUX_TEST="${MYLIB}/linux/linux-test/linux-test.elf"
BUSYBOX="${HOME}/code/linux/busybox-1.27.2"

if [ -f ./rootfs.img ]; then
    rm -rf ./rootfs.img
fi
if [ -f ./rootfs.img.gz ]; then
    rm -rf ./rootfs.img.gz
fi
if [ -d ./rootfs ]; then
    rm -rf ./rootfs
fi

mkdir -p rootfs
cd rootfs
sudo cp -rf ${BUSYBOX}/_install/* ./
sudo mkdir proc sys dev etc etc/init.d
sudo echo -e "#\!/bin/bash\nmount -t proc none /proc\nmount -t sysfs none /sys\n/sbin/mdev -s" > ./etc/init.d/rcS

find . | cpio -o --format=newc > ../rootfs.img
cd ..
gzip -c rootfs.img > rootfs.img.gz
