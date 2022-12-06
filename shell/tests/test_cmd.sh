#!/bin/bash

# 逐行遍历命令的执行结果
function traverse_cmd_resoult() {
    result=$(ls -l)
    echo "$result" # 加双引号会保留换行符
    # 逐行遍历结果
    echo "$result" | while read line
    do
        echo "each line: [$line]"
    done
}

function main() {
    traverse_cmd_resoult
}

main
