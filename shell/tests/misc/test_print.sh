#!/bin/bash
# shell向窗口打印多列
# 2024-04-26

LINE_OLD=""

function _print_to_tail() {
    local new="$1"
    local line_max=150
    local line=""
    local old_len=
    local new_len=
    local total_len=
    local need_cr=1
    #local old="${@:2}"

    #line=$(printf "%s %s" "$old" "$new")
    if [ "$LINE_OLD" == "" ]; then
        line=$(printf "%8s" "$new")
    else
        old_len=${#LINE_OLD}
        new_len=${#new}
        total_len=$(expr $old_len + $new_len)
        if [ $total_len -gt $line_max ]; then
            need_cr=0
            line=$(printf "%8s" "$new")
        else
            line=$(printf "%s%8s" "$LINE_OLD" "$new")
        fi
    fi
    LINE_OLD="$line"
    if [ "$need_cr" == "0" ]; then
        echo ""
    else
        echo -e "\r\c"
    fi
    echo -n "$line"
}

function test_print_col() {
    echo "$FUNCNAME:-----------------------------------------------------------"

    local i

    for i in $(seq 1 100000); do
        _print_to_tail $i
    done
    echo ""
}

function main() {
    test_print_col
}

main $*
