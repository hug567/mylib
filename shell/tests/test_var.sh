#!/bin/bash

# 判断变量是否为空
function var_is_null() {
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

function main() {
    var_is_null
}

main
