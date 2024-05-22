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

    # 查看子串在字符串中的起始位置, 索引从1开始
    echo "只有一个子串时：----------"
    local subStr="world"
    local str2="hello world"
    # 子串不存在时结果为0
    local start=$(awk -v a="${str2}" -v b="${subStr}" 'BEGIN{print index(a,b)}')
    echo "start: ${start}"
    if [ ${start} -gt 0 ]; then
        local end=$(expr ${start} + ${#subStr} - 1)
        echo "end: ${end}"
    else
        echo "there is no [${subStr}] in [${str2}]"
    fi

    # 有多个子串时，返回的是第一个子串的起始下标位置，下标从1开始
    echo "有多个子串时：----------"
    local sub2="o"
    local start=$(awk -v a="${str2}" -v b="${sub2}" 'BEGIN{print index(a,b)}')
    echo "start: ${start}"
}

function main() {
    test_str_find
}

main $*
