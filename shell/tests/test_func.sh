#!/bin/bash

_func_success() {
    ls > /dev/null
    return $?
}

_func_failed() {
    ls xxxzzzxxx > /dev/null 2>&1
    return $?
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

    # 在if中执行命令并判断返回值
    if [ $(_func_success; echo $?) -eq 0 ]; then
        echo "$fname run success with ret: $?"
    else
        echo "$fname run fail with ret: $?"
    fi

    # 第二种判断函数是否成功的方式，推荐
    local fname="_func_failed"
    _func_failed
    local ret=$?
    if [ "$ret" = "0" ]; then
        echo "$fname run success with ret: $?"
    else
        echo "$fname run fail with ret: $?"
    fi

    # 在if中执行命令并判断返回值
    if [ $(_func_failed; echo $?) -eq 0 ]; then
        echo "$fname run success with ret: $?"
    else
        echo "$fname run fail with ret: $?"
    fi
}

main() {
    test_func_ret
}

main
