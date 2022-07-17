#!/bin/bash

START_TIME=$(date +%s)
CUR_SOURCE_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
source ${CUR_SOURCE_DIR}/common.sh

CPU_THREAD_NUM=`cat /proc/cpuinfo |grep "processor"|wc -l`

check_files_exist ../applets/busybox.mkll

#make clean; make mrproper
log_info "You can run clean cmd: make clean; make mrproper"

# 生成.config配置文件
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig
sed -i "s/# CONFIG_STATIC is not set/CONFIG_STATIC=y/" .config

# 编译busybox
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j3

# 安装
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- install

# 制作rootfs
END_TIME=$(date +%s)
log_info "time spend: $(time_diff ${END_TIME} ${START_TIME})"
log_info "make rootfs: ~/code/mylib/linux/shell/make-rootfs-aarch64.sh"
