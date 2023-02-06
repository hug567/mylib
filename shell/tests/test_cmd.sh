#!/bin/bash

# 逐行遍历命令的执行结果
function traverse_cmd_result() {
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
    echo "get cmd return value"
    ls || exit # 命令执行失败将退出当前脚本
}

function main() {
    traverse_cmd_result
}

main
