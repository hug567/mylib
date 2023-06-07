#!/bin/bash

function _func_return() {
    return $1  # echo only return int
}

function _func_echo() {
    echo $1  # can echo any type of data
}

# get function return value
function test_get_func_ret() {
    echo "$FUNCNAME:-----------------------------"
    local ret=

    _func_return 0
    ret=$?  # $?: function return value
    echo "_func_return ret: $ret"
    _func_return 123
    ret=$?  # $?: function return value
    echo "_func_return ret: $ret"

    # determine whether cmd is successful according to the return value
    # check function return value in if statement
    if _func_return 0; then  # return 0: if is true
        echo "_func_return run success"
    fi
    # negate the return value
    if ! _func_return 123; then  # return not 0: if is false
        echo "_func_return run failed"
    fi

    echo "_func_echo 0: $(_func_echo 0)"
    echo "_func_echo 456: $(_func_echo 456)"
    echo "_func_echo 'test_string': $(_func_echo 'test_string')"
    # check function echo value in if statement
    if [ "$(_func_echo "12345")" = "12345" ]; then
        echo "_func_echo is 12345"
    fi
}

_func_success() {
    return 0
}

_func_failed() {
    return 123
}

# 判断函数是否执行成功
test_func_ret() {
    echo "$FUNCNAME:-----------------------------"

    # 第一种判断函数是否成功的方式
    local fname="_func_success"
    _func_success
    if [ $? -eq 0 ]; then
        echo "$fname run success with ret: $?"
    else
        echo "$fname run fail with ret: $?"
    fi

    # 在if中执行命令并判断返回值，推荐用法
    if _func_success; then
        echo "$fname run success with ret: $?"
    else
        echo "$fname run fail with ret: $?"
    fi

    # 对执行结果取反
    if ! _func_success; then
        echo "$fname run success with ret: $?"
    else
        echo "$fname run fail with ret: $?"
    fi

    # 第二种判断函数是否成功的方式
    local fname="_func_failed"
    _func_failed
    local ret=$?
    if [ "$ret" = "0" ]; then
        echo "$fname run success with ret: $?"
    else
        echo "$fname run fail with ret: $?"
    fi

    # 在if中执行命令并判断返回值，函数带返回值，推荐用法
    if _func_failed; then
        echo "$fname run success with ret: $ret"
    else
        echo "$fname run fail with ret: $?"
    fi
}

function _greater_10() {
    local num=$1
    if [ $num -gt 10 ]; then
        return 0  # true
    else
        return 1  # false
    fi
}

function test_return_bool() {
    echo "$FUNCNAME:-----------------------------"

    local num=11
    if _greater_10 $num; then  # true
        echo "$num > 10"
    fi

    num=9
    if ! _greater_10 $num; then  # ! false
        echo "$num <= 10"
    fi
}

function __pass_true() {
    _func_return 0
    return $?
}

function __pass_false() {
    _func_return 123
    return $?
}

# Passing return values between functions
function test_pass_ret() {
    echo "$FUNCNAME:-----------------------------"

    if __pass_true; then
        echo "pass true between functions"
    fi

    if ! __pass_false; then
        echo "pass false between functions"
    fi
}

main() {
    test_get_func_ret
    test_func_ret
    test_return_bool
    test_pass_ret
}

main
