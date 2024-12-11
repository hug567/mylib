#!/bin/bash

# sed常用正则表达式
function test_sed_regex() {
    echo "$FUNCNAME:-----------------------------"

    # 匹配4个连续数字
    echo "$(echo file-0001.txt | sed 's/^file-\([0-9]\{4\}\)\.txt/\1/g')"
}

function main() {
    test_sed_regex
}

main
