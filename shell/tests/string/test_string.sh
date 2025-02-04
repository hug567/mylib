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
# split/division the string according to the specified character
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

    echo "test_awk: ----------"
    local string="123:456:789"
    local div=$(echo $string | awk -F ':' '{ for (i=1; i<=$NF; i++) print$i }')
    for str in ${div[@]}; do
        echo "str: $str"
    done
}

# 字符串中存在指定的子串
function test_sub_exist() {
    echo "$FUNCNAME:-----------------------------"

    local str="helloworld"
    local sub="hello"

    # wildcard character
    if [[ -n "$sub" && "$str" == *"$sub"* ]]; then
        echo "[**] $sub exist in $str"
    fi

    # grep
    if [ "$(echo $str | grep $sub)" != "" ]; then
        echo "[grep] $sub exist in $str"
    fi

    # case in
    case "$str" in # helloworld
        *"$sub"*) # *hello*
            echo "[case] $sub exist in $str"
            ;;
        *)
            echo "[case] $sub does not exist in $str"
            ;;
    esac

    # =~
    if [[ $str =~ $sub ]]; then
        echo "[=~] $sub exist in $str"
    fi
}

# 判断字符是否为空
function test_str_empty() {
    echo "$FUNCNAME:-----------------------------------------------------------"

    local str1=
    if [ "${str1}" == "" ]; then
        echo "str1 is empty"
    fi
}

function main() {
    test_string_cut
    test_string_length
    test_string_split
    test_sub_exist
    test_str_empty
}

main
