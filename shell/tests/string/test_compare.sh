#!/bin/bash

# 正则表达式字符串比较
function test_comp_regular() {
    echo "$FUNCNAME:-----------------------------"

    # 字符串头部有指定字符
    local str1="hello world"
    if [[ $str1 =~ ^hello* ]]; then
        echo "str1 has string \"hello\" in the header"
    fi
}

function main() {
    test_comp_regular
}

main $*
