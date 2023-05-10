#!/bin/bash

function test_argv() {
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

function main() {
    test_argv $*
}

main $*
