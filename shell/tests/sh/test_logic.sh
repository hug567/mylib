#!/bin/sh
# sh中逻辑运算

# sh判断变量是否为空
test_logic() {
    echo "[test_logic]:--------------------------------------------------------"

    local num=10
    local str="hello"

    # 与：-a
    if [ ${num} -eq 10 -a "${str}" = "hello" ]; then
        echo "num is 10 and str is hello"
    fi

    # 或：-o，同时多个条件换行书写
    if [ ${num} -eq 11 -o \
         "${str}" = "hello" ]; then
        echo "num is 11 or str is hello"
    fi

    # 非：!
    if [ ! ${num} -eq 12 ]; then
        echo "num is not 12"
    fi
}

main() {
    test_logic
}

main
