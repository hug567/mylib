#!/bin/bash

# 替换字符截取
function test_cut() {
    echo "$FUNCNAME:-----------------------------"

    # 截取带有空格的字符串
    local str01="My name is Tom"
    echo "str01: [${str01[@]}]"
    # 下标从0开始，从str(3)截取到末尾，保留str(3)
    local str02=${str01[@]:3}
    echo "str02: [${str02[@]}]"

    # 使用tail截取字符串
    local len=${#str01}
    local tail_len=$(expr $len - 3) # 去掉头部3个元素，从第4个开始保留
    echo "str01 len: $len, tail_len: $tail_len"
    local str03=$(echo -n "$str01" | tail -c $tail_len)
    echo "str03: [${str03[@]}]"
}

function main() {
    test_cut
}

main $*
