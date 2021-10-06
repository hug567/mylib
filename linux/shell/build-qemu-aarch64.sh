#!/bin/bash

START_TIME=$(date +%s)

source ${MYLIB}/linux/shell/common.sh

check_in_build_dir

# 删除编译生成文件
#make clean

# 删除编译生成文件与配置文件
#make mrproper

# 生成.config配置文件
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig

# 编译内核
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j${CPU_THREAD_NUM}

# 编译内核模块(.ko)
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- modules -j${CPU_THREAD_NUM}

# 编译dts文件(生成dtb文件)
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- dtbs -j${CPU_THREAD_NUM}

# qemu启动命令
log_info "Run kernel: ~/code/mylib/linux/shell/qemu-run-aarch64.sh"
