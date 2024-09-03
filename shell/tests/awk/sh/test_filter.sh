#!/bin/bash
# awk过滤
# 2024-09-03

function test_filter() {
    echo "$FUNCNAME:-----------------------------"

    local str1=$(ls -l /)

    # 只打印包含指定字符串的行，$0：整行内容
    echo "${str1}" | awk '/dev/ {print $0}'
}

function main() {
    test_filter
}

main
