#!/bin/bash
# 字符串匹配
# 2024-09-10

# 字符串匹配
function test_match() {
    echo "$FUNCNAME:-----------------------------"

    # 判断是否以指定字符串结尾
    local str01="myfile.txt"
    if [[  "${str01}" =~ .*\.txt$ ]]; then
        echo "there is a txt file"
    fi
}

function main() {
    test_match
}

main $*
