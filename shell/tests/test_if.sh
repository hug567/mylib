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
    # if同时判断函数返回值与字符串比较：与
    if __return_true && [ $name == "Bob" ]; then
        echo "my name is Bob"
    fi
}

function test_func_ret_or_cmp() {
    echo "$FUNCNAME:-----------------------------"

    local name="Tom"
    # if同时判断函数返回值与字符串比较：或
    if __return_false || [ $name == "Tom" ]; then
        echo "my name is Tom"
    fi

    # if多条件判断中使用：非
    if ! __return_false || [ "$name" == "Bob" ]; then
        echo "not return false or my name is Bob"
    fi

    # if同时判断两个函数的返回值：或
    if __return_false || __return_true; then
        echo "At least one of the two conditions is true"
    fi
}

function __my_age() {
    local age=$1

    # if多分支判断：if-elif-else
    if [ $age -lt 10 ]; then
        echo "age < 10"
    elif [ $age -lt 20 ]; then
        echo "10 <= age < 20"
    else
        echo "age > 20"
    fi

    # if中多个比较条件：或
    if [ $age -lt 10 -o $age -gt 20 ]; then
        echo "age($age) < 10 or age($age) > 20"
    fi
    # if中多个比较条件：与
    if [ $age -gt 10 -a $age -lt 20 ]; then
        echo "10 < age($age) < 20"
    fi
    # if同时判断数值比较与函数返回值：与
    if [ $age -gt 20 ] && __return_true; then
        echo "age > 20 and cmd ret true"
    fi
}

function test_if_elif() {
    echo "$FUNCNAME:-----------------------------"
    __my_age 6
    __my_age 18
    __my_age 23
}

function main() {
    test_func_ret_and_cmp
    test_func_ret_or_cmp
    test_if_elif
}

main
