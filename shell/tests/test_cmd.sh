#!/bin/bash

# 逐行遍历命令的执行结果
function traverse_cmd_result() {
    echo -e "\n[function]: $FUNCNAME"
    local result=$(ls -l)
    echo "$result" # 加双引号会保留换行符
    # 逐行遍历结果
    echo "$result" | while read line
    do
        echo "each line: [$line]"
    done
}

# 判断命令返回值
function cmd_ret() {
    echo -e "\n[function]: $FUNCNAME"
    echo "get cmd return value"
    ls || exit # 命令执行失败将退出当前脚本
}

# echo输出换行
function echo_long_line() {
    echo -e "\n[function]: $FUNCNAME"
    echo "line 1" \
         "line 2" \
         "line 3"
}

function main() {
    traverse_cmd_result
    echo_long_line
}

main
