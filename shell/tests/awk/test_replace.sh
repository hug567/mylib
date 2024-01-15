#!/bin/bash
# awk字符串替换
# 2024-01-15

function test_replace_str() {
    echo "$FUNCNAME:-----------------------------"

    local str="123 456 789 123"
    echo "str: $str"

    # 只替换第一个匹配的子串
    local str01=$(echo "$str" | awk '{sub(/123/,"abc"); print$0}')
    echo "str01: $str01"

    # 替换所有匹配的子串
    local str02=$(echo "$str" | awk '{gsub(/123/,"abc"); print$0}')
    echo "str02: $str02"
}

function main() {
    test_replace_str
}

main
