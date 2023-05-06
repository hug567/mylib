#!/bin/bash

function test_shift() {
    echo "$FUNCNAME:-----------------------------"
    echo "param num: $#"
    while [ -n "$1" ]; do
        echo "param: $1"
        shift
    done
}

function test_get_operation() {
    echo "$FUNCNAME:-----------------------------"
    local name=
    local age=
    local print=

    while [ -n "$1" ]; do
        case $1 in
            -a) age=$2; shift;;
            -n) name=$2; shift;;
            -p) print=1;;
        esac
        shift
    done
    if [[ ${print} = 1 ]]; then
        echo "name: $name, age: $age"
    else
        echo "will not print student info"
    fi
}

function main() {
    test_shift var1 234 str3
    test_get_operation -a 18 -n Bob -p
    test_get_operation -a 19 -n Tom
}

main
