#!/bin/bash

function test_para_num() {
    echo "$FUNCNAME:-----------------------------"
    # 脚本参数个数
    echo $#
}

function test_pwd() {
    echo "$FUNCNAME:----------------------------------"
    # 当前目录
    cur_dir=$(pwd)
    echo "cur_dir = ${cur_dir}"
}

function test_dir_exist() {
    echo "$FUNCNAME:----------------------------"
    # 判断目录存在
    if [ -d ${cur_dir} ]; then
        echo "${cur_dir} does exist"
    fi

    # 判断目录不存在
    if [ ! -d ${cur_dir} ]; then
        echo "${cur_dir} does not exist"
    fi
}

function test_var_empty() {
    echo "$FUNCNAME:----------------------------"
    # 判断变量是否为空
    para01=
    if [ ! -n "$para01" ]; then
        echo "para01 is NULL"
    fi
    para01="xx"
    if [ -n "$para01" ]; then
        echo "para01 is not NULL: $para01"
    fi

    # 判断变量是否为空
    para02=
    if [ ! $para02 ]; then
        echo "para02 is NULL"
    fi
    para02="yy"
    if [ $para02 ]; then
        echo "para02 is not NULL: $para02"
    fi

    # 判断变量是否为空
    para03=
    if test -z $para03; then
        echo "para03 is NULL"
    fi
    para03="zz"
    if ! test -z $para03; then
        echo "para03 is not NULL: $para03"
    fi

    # 判断变量是否为空
    para04=
    if [ "$para04" = "" ]; then
        echo "para04 is NULL"
    fi
    para04="aa"
    if [ "$para04" != "" ]; then
        echo "para04 is not NULL: $para04"
    fi
}

# 数字比较
#   -gt：大于
#   -ge：大于等于
#   -lt：小于
#   -le：小于等于
#   -eq：等于
#   -ne：不等于
function test_num_cmp() {
    echo "$FUNCNAME:------------------------------"
    local num1=5
    local num2=4
    if [ $num1 -gt $num2 ]; then
        echo "$num1 > $num2"
    fi

    local num1=5
    local num2=5
    if [ $num1 -ge $num2 ]; then
        echo "$num1 >= $num2"
    fi

    local num1=4
    local num2=5
    if [ $num1 -lt $num2 ]; then
        echo "$num1 < $num2"
    fi

    local num1=5
    local num2=5
    if [ $num1 -le $num2 ]; then
        echo "$num1 <= $num2"
    fi

    local num1=5
    local num2=5
    if [ $num1 -eq $num2 ]; then
        echo "$num1 == $num2"
    fi

    local num1=5
    local num2=4
    if [ $num1 -ne $num2 ]; then
        echo "$num1 != $num2"
    fi
}

function main() {
    test_para_num $*
    test_pwd
    test_dir_exist
    test_var_empty
    test_num_cmp
}

main $*
