#!/bin/bash

START_TIME=$(date +%s)
CUR_SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${CUR_SCRIPT_DIR}/../../../; pwd)
source ${MYLIB}/linux/shell/common.sh

check_in_build_dir

log_info "CPU_THREAD = $CPU_THREAD"
log_info "COMPILE_THREAD = $COMPILE_THREAD"

# 删除编译生成文件
#make clean

# 删除编译生成文件与配置文件
#make mrproper

# 生成.config配置文件
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig

# 编译内核
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j$COMPILE_THREAD

# 编译内核模块(.ko)
#make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- modules -j$CPU_THREAD

# 编译dts文件(生成dtb文件)
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- dtbs -j$CPU_THREAD

# qemu启动命令
END_TIME=$(date +%s)
log_info "time spend: $(time_diff ${END_TIME} ${START_TIME})"
log_info "Run kernel: ~/code/mylib/linux/shell/aarch64/qemu_run_Image.sh"
