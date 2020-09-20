#!/bin/bash

BASE_DIR="${HOME}/code/linux"
BUSYBOX_DIR="${BASE_DIR}/busybox-1.27.2"
MYLIB="${HOME}/code/mylib"

cd ${BASE_DIR}
if [ -d rootfs ]; then
    sudo rm -rf rootfs
fi
mkdir rootfs
cd rootfs

echo "[INFO]: copy busybox file to rootfs"
sudo cp -rf ${BUSYBOX_DIR}/_install/* ./
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

echo "[INFO]: mknod tty device"
cd dev
sudo mknod -m 666 tty1 c 4 1
sudo mknod -m 666 tty2 c 4 2
sudo mknod -m 666 tty3 c 4 3
sudo mknod -m 666 tty4 c 4 4
sudo mknod -m 666 console c 5 1
sudo mknod -m 666 null c 1 3
cd ..

echo "[INFO]: copy test elf file to rootfs"
TEST_FILE="${MYLIB}/c/test-libc/obj/test-libc.elf "
TEST_FILE+="${MYLIB}/linux/linux-test/obj/linux-test.elf "
sudo cp -r ${TEST_FILE} tmp

echo "[INFO]: copy module ko file to rootfs"
MODULE_KO_FILE="${BASE_DIR}/linux-4.15/drivers/mytest/mytest.ko "
MODULE_KO_FILE+="${MYLIB}/linux/driver/test_char.ko "
MODULE_KO_FILE+="${MYLIB}/linux/driver/test_char2.ko "
MODULE_KO_FILE+="${MYLIB}/linux/driver/virt_net_driver.ko "
sudo cp -r ${MODULE_KO_FILE} lib/modules

echo "[INFO]: make rootfs.sd file"
cd ..
dd if=/dev/zero of=rootfs.sd bs=1M count=32
mkfs.ext3 rootfs.sd
sudo mount -t ext3 rootfs.sd /mnt -o loop
sudo cp -r rootfs/* /mnt
sudo umount /mnt

echo "[INFO]: delete temp file"
#sudo rm -rf rootfs
