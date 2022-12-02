#!/bin/bash

# 传递带空格的参数
function test_para_with_space() {
    para1="$1"
    echo "para1: [$para1]"
}

function main() {
    test_para_with_space " 123 "
}

main
