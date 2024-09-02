#!/bin/bash

# sed按正则表达式匹配截取字符串
function test_str_cut() {
    echo "$FUNCNAME:-----------------------------"

    local str01="my name is: Tom, and age is: 18"
    local str02="my name is: Jerry, and age is: 19"
    local str03="my name is: Bob, and age is: 20"

    # 使用正则表达式，从字符串中截取name
    local name=
    # 将匹配的字符串放在小括号中，再只保留匹配的字符串
    name=$(echo "${str01}" | sed 's/.*name is: \(.*\),.*/\1/g')
    echo "name: [${name}]"
    name=$(echo "${str02}" | sed 's/.*name is: \(.*\),.*/\1/g')
    echo "name: [${name}]"
    name=$(echo "${str03}" | sed 's/.*name is: \(.*\),.*/\1/g')
    echo "name: [${name}]"
}

function main() {
    test_str_cut
}

main
