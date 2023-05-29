#!/bin/bash

CUR_SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${CUR_SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/yocto/common.sh

function build_kernel() {
    local kernel_build=./tmp/work/qemuarm64-poky-linux/linux-yocto/5.15.32+gitAUTOINC+meta_machine-r0/linux-qemuarm64-standard-build
    local kernel_image=${kernel_build}/arch/arm64/boot/Image
    local latest_name=$(ls -l tmp/deploy/images/qemuarm64/Image-qemuarm64.bin | awk '{print$NF}')
    local deploy_image=./tmp/deploy/images/qemuarm64/${latest_name}

    check_dirs_exist $kernel_build
    ./tmp/work/qemuarm64-poky-linux/linux-yocto/5.15.32+gitAUTOINC+meta_machine-r0/temp/run.do_compile
    if [ $? != 0 ]; then
        log_error "------------------ compile kernel failed ------------------"
        exit 1
    fi
    cp $kernel_image $deploy_image
    md5sum $kernel_image $deploy_image
}

function main() {
    build_kernel
}

main
