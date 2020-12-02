#!/bin/bash

BASE_DIR=${HOME}/code/linux
MYLIB=${HOME}/code/mylib
BUSYBOX_DIR=${BASE_DIR}/busybox-1.27.2
CROCESS_COMPILER_DIR=${HOME}/tools/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabi
LIB_ROOTFS_DIR=${MYLIB}/linux/rootfs
ROOTFS=rootfs.sd

cd ${BASE_DIR}
if [ -d rootfs ]; then
    sudo rm -rf rootfs
fi
mkdir rootfs
cd rootfs

echo "[INFO]: copy busybox file to rootfs"
# bin  linuxrc  sbin  usr
sudo cp -rf ${BUSYBOX_DIR}/_install/* ./
sudo mkdir -p proc sys tmp root dev/pts etc/init.d usr/bin lib/modules
sudo cp ${LIB_ROOTFS_DIR}/etc/init.d/rcS etc/init.d/
sudo cp ${LIB_ROOTFS_DIR}/etc/profile etc/
sudo chmod a+x etc/init.d/rcS
sudo chmod a+x etc/profile

sudo cp ${LIB_ROOTFS_DIR}/etc/passwd etc/

echo "[INFO]: mknod tty device"
cd dev
sudo mknod -m 666 tty1 c 4 1
sudo mknod -m 666 tty2 c 4 2
sudo mknod -m 666 tty3 c 4 3
sudo mknod -m 666 tty4 c 4 4
sudo mknod -m 666 console c 5 1
sudo mknod -m 666 null c 1 3
cd ..

sudo cp -r ${CROCESS_COMPILER_DIR}/arm-linux-gnueabi/libc/lib/* lib

echo "[INFO]: copy test elf file to rootfs"
TEST_FILE="${MYLIB}/c/test-libc/obj/test-libc.elf "
TEST_FILE+="${MYLIB}/linux/linux-test/obj/linux-test.elf "
sudo cp -r ${TEST_FILE} tmp

echo "[INFO]: copy module ko file to rootfs"
#MODULE_KO_FILE="${BASE_DIR}/linux-4.15/drivers/mytest/mytest.ko "
MODULE_KO_FILE+="${MYLIB}/linux/driver/mybuild/test_char.ko "
MODULE_KO_FILE+="${MYLIB}/linux/driver/mybuild/mychar2.ko "
MODULE_KO_FILE+="${MYLIB}/linux/driver/mybuild/virt_net_driver.ko "
sudo cp -r ${MODULE_KO_FILE} lib/modules

echo "[INFO]: make rootfs file"
cd ..
dd if=/dev/zero of=${ROOTFS} bs=1M count=200
mkfs.ext3 ${ROOTFS}
sudo mount -t ext3 ${ROOTFS} /mnt -o loop
sudo cp -r rootfs/* /mnt
sudo umount /mnt

echo "[INFO]: delete temp file"
sudo rm -rf rootfs
