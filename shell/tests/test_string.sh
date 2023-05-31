#!/bin/bash

# 字符串截取
function test_string_cut() {
    echo "$FUNCNAME:-----------------------------"
    local str="0123456789"

    # 从左边第2个字符开始截取到末尾，保留第2个字符，下标从0开始
    local s=${str:2}
    echo "s = $s"
}

function test_string_length() {
    echo "$FUNCNAME:-----------------------------"
    local str=

    str="123456789"
    echo "string $str length: ${#str}"
    echo "string $str length: $(echo $str | awk '{print length($0)}')"
    echo "string $str length: $(echo $str | awk -F '' '{print NF}')"
    echo "string $str length: $(echo $str | wc -L)"
    echo "string $str length: $(echo -n $str | wc -c)"
    echo "string $str length: $(expr length $str)"
    echo "string $str length: $(expr $str : '.*')"
}

# 分隔字符串
function test_string_split() {
    echo "$FUNCNAME:-----------------------------"

    echo "test_replace: ----------"
    # 替换指定字符为空格
    local str="aaa:bbb:ccc:ddd"
    local arr=(${str//:/ })
    for sub in ${arr[@]}; do
        echo "sub: $sub"
    done

    echo "test_IFS: ----------"
    # 修改默认分隔符
    local IFS_OLD=$IFS
    IFS=$','
    local str="111,222,333"
    for sub in $str; do
        echo "sub: $sub"
    done
    IFS=$IFS_OLD

    echo "test_tr: ----------"
    # 使用tr替换字符为空格
    local str="Tom/Bob/Alice"
    local arr=($(echo $str | tr '/' ' '))
    for stu in ${arr[@]}; do
        echo "stu: $stu"
    done
}

function main() {
    test_string_cut
    test_string_length
    test_string_split
}

main
