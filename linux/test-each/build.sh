#!/bin/bash

BUILD_DIR=$PWD
SRC_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)

function check_cmd_exist() {
    local cmd=$1
    local ret=$(which $cmd)
    if [ -z "$ret" ]; then
        echo "cmd $cmd does not exist"
        exit 1
    fi
}

function main() {
    if [ "$BUILD_DIR" = "$SRC_DIR" ]; then
        echo "can not build in source dir"
        exit 1
    fi
    check_cmd_exist aarch64-linux-gnu-gcc
    cmake -DARCH=arm64 $SRC_DIR
    make
}

main $*
