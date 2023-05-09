#!/bin/bash

function test_continue() {
    echo "$FUNCNAME:-----------------------------"
    local i=

    for ((i=0; i < 5; i++)); do
        if [ $i -eq 3 ]; then
            # continue current loop
            echo
            continue
        fi
        echo "i = $i"
    done
}

function test_continue_n() {
    echo "$FUNCNAME:-----------------------------"
    local i=
    local j=

    for ((i=0; i < 3; i++)); do
        for ((j=0; j < 3; j++)); do
            if [ $i -eq 1 -a $j -eq 1 ]; then
                # continue multi loop
                echo
                continue 2
            fi
            echo "i = $i, j = $j"
        done
    done
}

function main() {
    test_continue
    test_continue_n
}

main
