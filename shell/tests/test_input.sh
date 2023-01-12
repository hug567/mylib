#!/bin/bash

function test_input() {
    echo "test_input_no_echo:"
    echo -n "please enter string: "
    read string
    echo "string: $string"
}

function test_input_no_echo() {
    echo "test_input_no_echo:"
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
