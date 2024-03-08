#!/usr/bin/sh

# sh判断变量是否为空
test_string_empty() {
    echo "[test_true_false]:-------------------------------"

    local var=
    # 只能用单个=，不能用==
    if [ "${var}" = "" ]; then
        echo "var is empty"
    else
        echo "var is not empty: ${var}"
    fi

    local var2="hello"
    if [ "${var2}" = "" ]; then
        echo "var2 is empty"
    else
        echo "var2 is not empty: ${var2}"
    fi
}

main() {
    test_string_empty
}

main
