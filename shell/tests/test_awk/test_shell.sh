#!/bin/bash
# Simply use awk in shell script
# 2023-06-21

function test_print_line() {
    echo "$FUNCNAME:-----------------------------"

    local str="123 456 789
aaa bbb ccc"
    # print line1
    # line: $1 $2 $3 ...
    # last line: $NF
    echo "$str" | awk '{print$1}'
}

function main() {
    test_print_line
}

main
