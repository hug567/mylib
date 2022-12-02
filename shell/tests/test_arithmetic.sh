#!/bin/bash

# 求余运算
function test_mod() {
    num=11
    let mod=num%10
    echo "mod = $mod"

    if [ $[11%10] = 1 ]; then
        echo "11 % 10 = 1"
    fi

    if [ $[20%10] = "0" ]; then
        echo "20 % 10 = 0"
    fi

    num=30
    if [ $[$num%10] = "0" ]; then
        echo "$num % 10 = 0"
    fi
}

function main() {
    test_mod
}

main
