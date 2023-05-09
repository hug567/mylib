#!/bin/bash

function test_break() {
    echo "$FUNCNAME:-----------------------------"
    local i=

    for ((i=0; i < 10; i++)); do
        echo "i = $i"
        if [ $i -eq 5 ]; then
            # break current loop
            break
        fi
    done
}

function test_break_n() {
    echo "$FUNCNAME:-----------------------------"
    local i=
    local j=

    for ((i=0; i < 10; i++)); do
        for ((j=0; j < 10; j++)); do
            echo "i = $i, j = $j"
            if [ $i -eq 1 -a $j -eq 5 ]; then
                # break multi loop
                break 2
            fi
        done
    done
}

function main() {
    test_break
    test_break_n
}

main
