#!/bin/bash

# 按空格分割字符串
function test_split_with_space() {
    echo "$FUNCNAME:-----------------------------"

    # 默认分隔符就是空格，不需要其他处理
    local str="My name is Tom"
    for member in ${str[@]}; do
        echo "member: $member"
    done
}

function main() {
    test_split_with_space
}

main $*
