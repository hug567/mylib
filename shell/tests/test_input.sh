#!/bin/bash

function test_input() {
    echo "$FUNCNAME:-----------------------------"
    echo -n "please enter string: "
    read string
    echo "string: $string"

    # specify a prompt in the read cmd
    read -p "please enter name: " name
    echo "name: $name"

    # timeout
    read -t 5 -p "please enter age in 5s: " age
    echo "age: $age"
}

function test_input_no_echo() {
    echo "$FUNCNAME:-----------------------------"
    echo -n "please enter passwd: "
    read -s passwd
    echo ""
    echo "passwd: $passwd"
}

function main() {
    test_input
    test_input_no_echo
}

main
