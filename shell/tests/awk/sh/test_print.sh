#!/bin/bash
# 2025-03-05

function test_print_str() {
    echo "$FUNCNAME:-----------------------------------------------------------"

    local lines=$(ls -l /)
    # awk print同时输出变量和字符串
    echo "${lines}" | awk '{print $1" - "$2" - "$3}'
    echo "${lines}" | awk '{print $1" , "$2" , "$3}'
}

function main() {
    test_print_str
}

main $*
