#!/bin/bash
# shell字符串查找
# 2024-04-18

# 字符串查找
function test_str_find() {
    echo "$FUNCNAME:-----------------------------"

    # 字符串中有指定子串
    local str1="hello world"
    local ret=$(echo "$str1" | grep "world")
    if [ "$ret" != "" ]; then
        echo "there is \"world\" in str1"
    fi
}

function main() {
    test_str_find
}

main $*
