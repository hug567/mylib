#!/bin/bash

# 判断变量是否为空
var_is_null() {
    local var1=
    if [ ! -n "$var1" ]; then
        echo "var1 is NULL"
    else
        echo "var1 is not NULL"
    fi

    local var2="12345"
    if [ -n "$var2" ]; then
        echo "var2 is not NULL: $var2"
    fi
}

function main() {
    var_is_null
}

main
