#!/bin/bash

function usage() {
    echo "Usage: $0 <dir>             need apply busybox build dir"
}

function make_gzip_rootfs() {
    local busybox_dir=$1

    rm -rf rootfs rootfs.cpio rootfs.cpio.gz
    mkdir rootfs
    cd rootfs

    echo "[INFO]: copy busybox file to rootfs"
    cp -rf ${busybox_dir}/_install/* ./
    #cp -rf $MYLIB/linux/rootfs/* .
    mkdir -p proc sys tmp dev/pts etc/init.d usr/bin lib/modules
    touch etc/init.d/rcS
    chmod a+x etc/init.d/rcS
    sh -c 'echo "#!/bin/sh" > etc/init.d/rcS'
    sh -c 'echo "mount -t proc none /proc" >> etc/init.d/rcS'
    sh -c 'echo "mount -t sysfs none /sys" >> etc/init.d/rcS'
    sh -c 'echo "/sbin/mdev -s" >> etc/init.d/rcS'
    sh -c 'echo "mount -t devpts devpts /dev/pts" >> etc/init.d/rcS'
    sh -c 'echo "telnetd" >> etc/init.d/rcS'
    sh -c 'echo "ifconfig eth0 192.168.1.101 netmask 255.255.255.0" >> etc/init.d/rcS'
    touch etc/passwd
    sh -c 'echo "root::0:0:root:/root:/bin/sh" > etc/passwd'

    echo "[INFO]: package rootfs.cpio"
    find . | cpio -o --format=newc > ../rootfs.cpio
    echo "[INFO]: gzip rootfs.cpio.gz"
    cd ..
    gzip -c rootfs.cpio > rootfs.cpio.gz
}

function main() {
    export MYLIB=$HOME/code/mylib
    local busybox_dir=$1
    if [ $# != 1 ] || [ ! -d $busybox_dir ]; then
        usage
        exit 1
    fi
    make_gzip_rootfs $busybox_dir
}

main $*
