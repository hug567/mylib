#!/bin/bash

# 判断变量是否为空
function test_var_is_null() {
    echo "$FUNCNAME:-----------------------------"

    local var1=
    if [ ! -n "$var1" ]; then
        echo "[!-n] var1 is NULL"
    fi
    if [ -z $var1 ]; then
        echo "[-z] var1 is NULL"
    fi

    local var2="12345"
    if [ -n "$var2" ]; then
        echo "[-n] var2 is not NULL: $var2"
    fi
    if [ ! -z "$var2" ]; then
        echo "[!-z] var2 is not NULL: $var2"
    fi
}

# bash内置变量
function test_builtin_var() {
    echo "$FUNCNAME:-----------------------------"

    echo "FUNCNAME = $FUNCNAME"
    echo "LINENO = $LINENO"
    echo "BASH_LINENO[*] = ${BASH_LINENO[*]}"
    echo "BASH_SOURCE[*] = ${BASH_SOURCE[*]}"
    echo "BASH_SOURCE[0] = ${BASH_SOURCE[0]}"
    echo "BASH_VERSION = $BASH_VERSION"
}

function main() {
    test_var_is_null
    test_builtin_var
}

main
