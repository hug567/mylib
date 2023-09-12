#!/bin/bash

#base_dir="${HOME}/code/linux"
base_dir="${PWD}"
#busybox_dir="${base_dir}/busybox-1.27.2"
busybox_dir="$HOME/code/busybox-1.35.0/build-arm"
rootfs_dir="${base_dir}/rootfs"

cd ${base_dir}
rm -rf rootfs rootfs.cpio rootfs.cpio.gz
mkdir rootfs
cd rootfs

echo "[INFO]: copy busybox file to rootfs"
sudo cp -rf ${busybox_dir}/_install/* ./
sudo mkdir -p proc sys tmp dev/pts etc/init.d usr/bin lib/modules
sudo touch etc/init.d/rcS
sudo chmod a+x etc/init.d/rcS
sudo sh -c 'echo "#!/bin/sh" > etc/init.d/rcS'
sudo sh -c 'echo "mount -t proc none /proc" >> etc/init.d/rcS'
sudo sh -c 'echo "mount -t sysfs none /sys" >> etc/init.d/rcS'
sudo sh -c 'echo "/sbin/mdev -s" >> etc/init.d/rcS'
sudo sh -c 'echo "mount -t devpts devpts /dev/pts" >> etc/init.d/rcS'
sudo sh -c 'echo "telnetd" >> etc/init.d/rcS'
sudo sh -c 'echo "ifconfig eth0 192.168.0.101 netmask 255.255.255.0" >> etc/init.d/rcS'
sudo touch etc/passwd
sudo sh -c 'echo "root::0:0:root:/root:/bin/sh" > etc/passwd'

echo "[INFO]: package rootfs.cpio"
find . | cpio -o --format=newc > ../rootfs.cpio

echo "[INFO]: gzip rootfs.cpio.gz"
cd ..
gzip -c rootfs.cpio > rootfs.cpio.gz

function usage() {
    echo "Usage: $0 <busybox_dir>"
}

function main() {
    echo "main"
}

main $*
