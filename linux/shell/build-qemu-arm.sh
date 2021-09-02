#!/bin/bash

START_TIME=$(date +%s)

source ${MYLIB}/linux/shell/common.sh

check_files_exist ../include/linux/kernel.h

# 删除编译生成文件
#make clean

# 删除编译生成文件与配置文件
#make mrproper

# 生成.config配置文件
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_defconfig

# 编译内核
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j${CPU_THREAD_NUM}

# 编译内核模块(.ko)
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- modules -j${CPU_THREAD_NUM}

# 编译dts文件(生成dtb文件)
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- dtbs -j${CPU_THREAD_NUM}

END_TIME=$(date +%s)
log_info "time spent: $(time_diff $END_TIME $START_TIME)"
# qemu启动命令
log_info "Run: ~/code/mylib/linux/shell/qemu-run-arm-zImage.sh"
