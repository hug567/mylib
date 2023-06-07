#!/bin/bash
#  $0：脚本文件名
#  $1：第1个参数，其他类似
#  $#：参数个数
#  #{$#}：最后一个参数
#  $*：所有参数，视为一个整体
#  $@：所有参数，视为同一字符中的多个单词，可使用for param in "$@"遍历

# 逐行遍历命令的执行结果
function test_traverse_cmd_result() {
    echo "$FUNCNAME:-----------------------------"
    local result=$(ls -l)
    # echo "$result" # 加双引号会保留换行符
    # 逐行遍历结果
    echo "$result" | while read line
    do
        echo "line: [$line]"
    done

    echo "[test \\r]: ----------"
    # 原始字符串以\r作为换行符，使用sed替换为\n
    local content=$(echo -e "line 1\rline 2\rline 3\r")
    content=$(echo $content | sed 's/\r/\n/g')
    echo "$content" | while read item
    do
        echo "item: [$item]"
    done
}

# 判断命令返回值
function test_cmd_ret() {
    echo "$FUNCNAME:-----------------------------"
    echo "get cmd return value"
    ls || exit # 命令执行失败将退出当前脚本

    ls > /dev/null
    if [ $? -eq 0 ]; then
        echo "run cmd success: ls"
    fi
}

# echo输出换行
function test_echo_long_line() {
    echo "$FUNCNAME:-----------------------------"
    echo "line 1" \
         "line 2" \
         "line 3"
}

# using which
function __cmd_exist() {
    local cmd=$1
    if which $cmd &> /dev/null; then
        echo "$cmd exist"
    else
        echo "$cmd not exist"
    fi
}

# using type and check rerurn value
function __cmd_exist_2() {
    local cmd=$1
    local ret=$(type "$cmd" 2>&1 | grep "not found")
    if [ "$ret" == "" ]; then
        echo "$cmd exist"
    else
        echo "$cmd not exist"
    fi
}

function test_cmd_exist() {
    echo "$FUNCNAME:-----------------------------"

    __cmd_exist cmake
    __cmd_exist xxx
    __cmd_exist_2 vim
    __cmd_exist_2 yyy
}

function main() {
    test_traverse_cmd_result
    test_echo_long_line
    test_cmd_ret
    test_cmd_exist
}

main
