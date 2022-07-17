#!/bin/bash

START_TIME=$(date +%s)
CUR_SCRIPT_DIR=$(cd $(dirname $0); pwd)
CUR_SOURCE_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
source ${CUR_SOURCE_DIR}/common.sh

ROOTFS=rootfs.raw
SDK_PATH=${HOME}/code/linux/sdk/aarch64
LIB_ROOTFS_DIR=$(cd ${CUR_SOURCE_DIR}/../rootfs; pwd)
#CROCESS_COMPILER_DIR=${HOME}/tools/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabi

check_in_build_dir

if [ -d rootfs ]; then
    sudo rm -rf rootfs
fi
mkdir rootfs
cd rootfs

cp -rf ${SDK_PATH}/busybox/* ./

mkdir -p proc sys tmp root dev/pts etc/init.d usr/bin lib/modules
cp ${LIB_ROOTFS_DIR}/etc/init.d/rcS etc/init.d/
cp ${LIB_ROOTFS_DIR}/etc/profile etc/
chmod a+x etc/init.d/rcS
chmod a+x etc/profile
cp ${LIB_ROOTFS_DIR}/etc/passwd etc/

find . | cpio -o --format=newc > ../rootfs.cpio
cd ..
gzip -c rootfs.cpio > rootfs.gzip

END_TIME=$(date +%s)
log_info "time spent: $(time_diff $END_TIME $START_TIME)"
