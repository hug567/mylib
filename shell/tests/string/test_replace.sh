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

    # 下划线替换未换行符
    local str05="my_name_is_Tom"
    local str06=$(echo "${str05}" | sed "s/_/\n/g")
    echo "${str06}"
}

function main() {
    test_replace_one_char
}

main $*
