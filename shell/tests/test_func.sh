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

main() {
    test_get_func_ret
    test_func_ret
}

main
