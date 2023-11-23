#!/bin/bash
# run awk script file
# 2023-06-21

function test_awk_normal() {
    echo "$FUNCNAME:-----------------------------"

    local file=/tmp/test_awk.txt
    if [ ! -f $file ]; then
        touch $file
    fi
    awk -f hello.awk $file
    rm $file
}

function main() {
    test_awk_normal
}

main
