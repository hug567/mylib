#!/bin/bash

# 替换字符串中单个字符
function test_replace_one_char() {
    echo "$FUNCNAME:-----------------------------"

    local str01="My,Name,Is,Tom(age,18)"
    # 逗号替换为空格
    local str02=(${str01//,/ })
    # 字符串中有空格，然后左括号替换为空格
    local str03=(${str02[@]//\(/ })
    # 字符串中有空格，然后右括号替换为空格
    local str04=(${str03[@]//\)/ })
    echo "str01: [$str01]"
    echo "str02: [${str02[@]}]"
    echo "str03: [${str03[@]}]"
    echo "str04: [${str04[@]}]"
}

function main() {
    test_replace_one_char
}

main $*
