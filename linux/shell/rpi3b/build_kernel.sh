#!/bin/bash

START_TIME=$(date +%s)
CUR_SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${CUR_SCRIPT_DIR}/../../../; pwd)
source ${MYLIB}/linux/shell/common.sh

check_files_exist ../include/linux/kernel.h

make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- bcmrpi3_defconfig

make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j3

END_TIME=$(date +%s)
log_info "time spend: $(time_diff ${END_TIME} ${START_TIME})"
