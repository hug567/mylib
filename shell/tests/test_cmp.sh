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

function test_n_var() {
    echo "$FUNCNAME:----------------------------"
    # 判断变量是否为空
    para01=
    if [ ! -n "$para01" ]; then
        echo "para01 is NULL"
    fi
    para01="xx"
    if test -n "$para01" ; then
        echo "[test -n] para01 is not NULL: $para01"
    fi
    if [ -n "$para01" ]; then
        echo "[-n] para01 is not NULL: $para01"
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
}

function test_z_var() {
    echo "$FUNCNAME:----------------------------"
    # 判断变量是否为空
    para03=
    if test -z "$para03"; then
        echo "[test -z] para03 is NULL"
    fi
    if [ -z "$para03" ]; then
        echo "[-z] para03 is NULL"
    fi
    para03="zz"
    if ! test -z "$para03"; then
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

# 数字比较
#   >：大于
#   <：小于
#   ==：等于
#   !=：不等于
#   &&：与
#   ||：或
function test_num_cmp_02() {
    echo "$FUNCNAME:------------------------------"
    if [[ 5 > 4 ]]; then
        echo "5 > 4"
    fi

    # >=
    if [[ 5 > 5 || 5 == 5 ]]; then
        echo "5 >= 5"
    fi

    if [[ 4 < 5 ]]; then
        echo "4 < 5"
    fi

    # <=
    if [[ 4 < 4 || 4 == 4 ]]; then
        echo "4 <= 4"
    fi

    if [[ 3 == 3 ]]; then
        echo "3 == 3"
    fi

    if [[ 3 != 2 ]]; then
        echo "3 != 2"
    fi
}

# 字符串比较：
#   =：等于
#   !=：不等于
#   >：大于
#   <：小于
#   -n：字符串长度不为0
#   -z：字符串长度为0
function test_string_cmp() {
    echo "$FUNCNAME:-----------------------------"
    local str1=
    local str2=

    # test string equal
    str1="str123"
    str2="str123"
    if [ ${str1} = ${str2} ]; then
        echo "$str1 = $str2"
    fi
    if [ "${str1}" == "${str2}" ]; then
        echo "$str1 == $str2"
    fi

    # test string not equal
    str1="str123"
    str2="str456"
    if [ ${str1} != ${str2} ]; then
        echo "$str1 != $str2"
    fi

    # test string greater than
    str1="456"
    str2="1234"
    if [ ${str1} \> ${str2} ]; then
        echo "$str1 > $str2"
    fi

    # test string less than
    str1="1234"
    str2="456"
    if [ ${str1} \< ${str2} ]; then
        echo "$str1 < $str2"
    fi

    # test string length is not 0
    str1="123"
    if [ -n ${str1} ]; then
        echo "str1 length is not 0, length: ${#str1}"
    fi

    # test string length is 0
    str1=""
    if [ -z ${str1} ]; then
        echo "str1 length is 0"
    fi
}

function main() {
    test_para_num $*
    test_pwd
    test_dir_exist
    test_n_var
    test_z_var
    test_num_cmp
    test_num_cmp_02
    test_string_cmp
}

main $*
