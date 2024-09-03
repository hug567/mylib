#!/bin/bash
# awk数学计算
# 2024-09-03

function test_add() {
    echo "$FUNCNAME:-----------------------------"

    local str1="1 2 3 4 5 6 7 8 9"
    # 空格替换为换行
    local str2=$(echo "${str1}" | sed 's/ /\n/g')

    # 计算所有行第一列数的和
    local sum=$(echo "${str2}" | awk '{sum += $1} END{print sum}')
    echo "sum: ${sum}"
}

function main() {
    test_add
}

main
