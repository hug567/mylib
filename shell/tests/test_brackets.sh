#!/bin/bash

function test_double_brackets() {
    echo "$FUNCNAME:-----------------------------"
    if (( 2 * 5 > 9 )); then
        echo "2 * 5 > 9"
    fi

    # 2 ^ 4 = 16
    if (( 2 ** 4 > 9 )); then
        echo "2 ** 4 > 9, 2 ** 4 = $((2 ** 4))"
    fi
}

function test_brackets_for() {
    echo "$FUNCNAME:-----------------------------"
    for (( i=0; i < 10; i++ )); do
        echo "i = $i"
    done
}

function main() {
    test_double_brackets
    test_brackets_for
}

main $*
