#!/bin/bash

using_env_var() {
    # 变量是否存在
    if [ $G_TEST_VAR ]; then
        echo "G_TEST_VAR already defined: $G_TEST_VAR"
    else
        echo "G_TEST_VAR is not exist"
    fi

    # 变量是否为空
    if [ -z $G_TEST_VAR ]; then
        echo "G_TEST_VAR is NULL"
    else
        echo "G_TEST_VAR already defined: $G_TEST_VAR"
    fi
}

function main() {
    using_env_var
}

main
