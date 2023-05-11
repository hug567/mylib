#!/bin/bash

function test_args() {
    echo "$FUNCNAME:-----------------------------"
    # 脚本参数个数
    echo "argc = $#"

    # 所有输入参数
    echo "all args: $*"

    # 访问输入参数
    i=1
    for argv in $*; do
        echo "argv[$i] = $argv"
        let i+=1
    done
}

function test_get_part_args() {
    echo "$FUNCNAME:-----------------------------"

    echo "all args: $*"
    echo "from 1 and get 2 args: ${*:1:2}"
    echo "from 2 and get 2 args: ${*:2:2}"
    echo "from 2 to end: ${*:2}"
}

function main() {
    test_args arg1 arg2 333 456
    test_get_part_args arg1 arg2 333 456
}

main
