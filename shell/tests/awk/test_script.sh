#!/bin/bash

function test_awk_normal() {
    echo "$FUNCNAME:-----------------------------"

    local file=/tmp/test_awk.txt
    awk -f hello.awk $file
}

function main() {
    test_awk_normal
}

main
