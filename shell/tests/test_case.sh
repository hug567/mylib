#!/bin/bash

function _test_case() {
    local var=$1
    case $var in
        1)
            echo "var is 1"
            ;;
        2)
            echo "var is 2"
            ;;
        3|4)
            echo "var is 3 or 4"
            ;;
        *)
            echo "unknown var: $var"
    esac
}

function test_case() {
    echo "$FUNCNAME:-----------------------------"
    _test_case 1
    _test_case 2
    _test_case 3
    _test_case 4
    _test_case 5
}

function main() {
    test_case
}

main
