#!/bin/bash

source $MYLIB/linux/shell/common.sh

BASE_DIR=${HOME}/code/linux
#MYLIB=${HOME}/code/mylib
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

log_info "copy busybox file to rootfs"
# bin  linuxrc  sbin  usr
cp -rf ${BUSYBOX_DIR}/_install/* ./

log_info "copy configure file to rootfs"
mkdir -p proc sys tmp root dev/pts etc/init.d usr/bin lib/modules
cp ${LIB_ROOTFS_DIR}/etc/init.d/rcS etc/init.d/
cp ${LIB_ROOTFS_DIR}/etc/profile etc/
chmod a+x etc/init.d/rcS
chmod a+x etc/profile

cp ${LIB_ROOTFS_DIR}/etc/passwd etc/

log_info "mknod tty device"
cd dev
sudo mknod -m 666 tty1 c 4 1
sudo mknod -m 666 tty2 c 4 2
sudo mknod -m 666 tty3 c 4 3
sudo mknod -m 666 tty4 c 4 4
sudo mknod -m 666 console c 5 1
sudo mknod -m 666 null c 1 3
cd ..

log_info "copy lib files [lib]"
cp -r ${CROCESS_COMPILER_DIR}/arm-linux-gnueabi/libc/lib/* lib

copy_file_to_tmp ${MYLIB}/c/test-libc/obj/test-libc.elf
copy_file_to_tmp ${MYLIB}/linux/linux-test/obj/linux-test.elf
copy_file_to_tmp ${MYLIB}/linux/driver/test.sh

TEST_DRIVER_DIR=${MYLIB}/linux/driver/mybuild
copy_file_to_lib_modules ${TEST_DRIVER_DIR}/test_char.ko
copy_file_to_lib_modules ${TEST_DRIVER_DIR}/mychar2.ko
copy_file_to_lib_modules ${TEST_DRIVER_DIR}/virt_net_driver.ko
copy_file_to_lib_modules ${TEST_DRIVER_DIR}/vexpress/myuart.ko

log_info "make rootfs file"
cd ..
dd if=/dev/zero of=${ROOTFS} bs=1M count=200
mkfs.ext3 ${ROOTFS}
sudo mount -t ext3 ${ROOTFS} /mnt -o loop
sudo cp -r rootfs/* /mnt
sudo umount /mnt

log_info "delete temp file"
sudo rm -rf rootfs
