#!/bin/bash

# getopt不能处理带空格的参数
function _test_getopt() {
    local name=
    local age=
    local short=

    set -- $(getopt a:n:s "$@")
    while [ -n "$1" ]; do
        case $1 in
            -n) name=$2; shift;;
            -a) age=$2; shift;;
            -s) short=1;;
        esac
        shift
    done
    if [[ $short = 1 ]]; then
        echo "Student: $name/$age"
    else
        echo "Student name: $name, age: $age"
    fi
}

function test_getopt() {
    echo "$FUNCNAME:-----------------------------"
    _test_getopt -n Bob -a 18 -s
    _test_getopt -n Tom -a 19
}

function main() {
    test_getopt
}

main
