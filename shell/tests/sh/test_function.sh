#!/bin/sh

# sh的函数不需要function关键字声明
test_return() {
    echo "[test_function]:-------------------------------"

    echo "log before return"
    return
    # return后的语句不会执行
    echo "log after return"
}

main() {
    test_return
}

main
