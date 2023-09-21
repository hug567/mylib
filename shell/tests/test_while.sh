#!/bin/bash

function test_while() {
    echo "$FUNCNAME:-----------------------------"

    local num=0
    while [ $num -lt 5 ]; do
        echo "cur in while loop, num: $num"
        let num=num+1
    done

    while true; do
        echo "cur in while true loop, num: $num"
        if [ $num -eq 0 ]; then
            break
        fi
        let num=num-1
    done
}

function main() {
    test_while
}

main
