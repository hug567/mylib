#!/bin/bash

function __return_true() {
    return 0
}

function __return_false() {
    return 1
}

function test_func_ret_and_cmp() {
    echo "$FUNCNAME:-----------------------------"

    local name="Bob"
    if __return_true && [ $name == "Bob" ]; then
        echo "my name is Bob"
    fi
}

function test_func_ret_or_cmp() {
    echo "$FUNCNAME:-----------------------------"

    local name="Tom"
    if __return_false || [ $name == "Tom" ]; then
        echo "my name is Tom"
    fi
}

function main() {
    test_func_ret_and_cmp
    test_func_ret_or_cmp
}

main
