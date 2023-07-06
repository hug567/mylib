#!/bin/bash
# 2023-07-06

# script for jenkins pipeline task test01
# jenkins will run this script in docker

set +x

function main() {
    echo "------------------------------------------------------------"
    env
    echo "------------------------------------------------------------"
    cd /data
    rm -rf build
    mkdir build
    cd build
    cmake /data/mylib/cmake/tests/test_comp_exec
    make
    ./hello.elf
}

main $*
