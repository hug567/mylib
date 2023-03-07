#!/bin/bash

export MYLIB=$(cd $(dirname $0)/../../..; pwd)
source $MYLIB/shell/lib/common.sh

LINUX_BUILD=
SOURCE_DIR=
BUILD_DIR=

usage() {
    echo "Usage:"
    echo "  $0 <linux build dir>"
}

prepare() {
    if [ $# != 1 ]; then
        usage
        exit
    fi
    LINUX_BUILD=$1
    check_files_exist $LINUX_BUILD/include/generated/autoconf.h
    SOURCE_DIR=$(cd $(dirname $0); pwd)
    BUILD_DIR=$LINUX_BUILD/mydriver
}

copy_files() {
    rm -rf $BUILD_DIR
    mkdir -p $BUILD_DIR
    cp $SOURCE_DIR/Makefile $BUILD_DIR
    cp $SOURCE_DIR/test_procfs.c $BUILD_DIR
}

compile_ko() {
    cd $LINUX_BUILD/mytests
    make -C $LINUX_BUILD M=$BUILD_DIR ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- modules
}

main() {
    prepare $*
    copy_files
    compile_ko
}

main $*
