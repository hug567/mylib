#!/bin/bash

source ${MYLIB}/linux/shell/common.sh

BASE_DIR=${HOME}/code/linux
MYLIB=${HOME}/code/mylib
BUSYBOX_DIR=${BASE_DIR}/sdk/virt-aarch64/busybox
#CROCESS_COMPILER_DIR=${HOME}/tools/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabi
ROOTFS=rootfs.aarch64

check_in_build_dir
check_dirs_exist ${BUSYBOX_DIR}

if [ -d rootfs ]; then
    sudo rm -rf rootfs
fi
mkdir rootfs
cd rootfs

log_info "copy busybox file to rootfs"
sudo cp -rf ${BUSYBOX_DIR}/* ./
sudo mkdir -p proc sys tmp root dev etc/init.d usr/bin lib/modules
sudo touch etc/init.d/rcS
sudo chmod a+x etc/init.d/rcS
sudo sh -c 'echo "#!/bin/sh" > etc/init.d/rcS'
sudo sh -c 'echo "mount -t proc proc /proc" >> etc/init.d/rcS'
sudo sh -c 'echo "mount -t sysfs sysfs /sys" >> etc/init.d/rcS'
sudo sh -c 'echo "mount -t tmpfs tmpfs /dev" >> etc/init.d/rcS'
sudo sh -c 'echo "mkdir -p /dev/pts" >> etc/init.d/rcS'
sudo sh -c 'echo "mount -t devpts devpts /dev/pts" >> etc/init.d/rcS'
sudo sh -c 'echo "/sbin/mdev -s" >> etc/init.d/rcS'
sudo sh -c 'echo "echo /sbin/mdev > /proc/sys/kernel/hotplug" >> etc/init.d/rcS'
sudo sh -c 'echo "telnetd" >> etc/init.d/rcS'
sudo sh -c 'echo "ifconfig eth0 192.168.0.101 netmask 255.255.255.0" >> etc/init.d/rcS'

sudo touch etc/passwd
sudo sh -c 'echo "root::0:0:root:/root:/bin/sh" > etc/passwd'

log_info "mknod tty device"
cd dev
sudo mknod -m 666 tty1 c 4 1
sudo mknod -m 666 tty2 c 4 2
sudo mknod -m 666 tty3 c 4 3
sudo mknod -m 666 tty4 c 4 4
sudo mknod -m 666 console c 5 1
sudo mknod -m 666 null c 1 3
cd ..

#sudo cp -r ${CROCESS_COMPILER_DIR}/arm-linux-gnueabi/libc/lib/* lib
#
#echo "[INFO]: copy test elf file to rootfs"
#TEST_FILE="${MYLIB}/c/test-libc/obj/test-libc.elf "
#TEST_FILE+="${MYLIB}/linux/linux-test/obj/linux-test.elf "
#sudo cp -r ${TEST_FILE} tmp
#
#echo "[INFO]: copy module ko file to rootfs"
#MODULE_KO_FILE="${BASE_DIR}/linux-4.15/drivers/mytest/mytest.ko "
#MODULE_KO_FILE+="${MYLIB}/linux/driver/test_char.ko "
#MODULE_KO_FILE+="${MYLIB}/linux/driver/test_char2.ko "
#MODULE_KO_FILE+="${MYLIB}/linux/driver/virt_net_driver.ko "
#sudo cp -r ${MODULE_KO_FILE} lib/modules

log_info "make rootfs file"
find . | cpio -o --format=newc > ../rootfs.cpio
cd ..
gzip -c rootfs.cpio > rootfs.gzip

ls -lh rootfs.gzip
