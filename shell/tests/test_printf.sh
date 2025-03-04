#!/bin/bash

# 格式化输出浮点数
function test_printf_float() {
    echo "$FUNCNAME:-----------------------------------------------------------"

    # 第一位小数四舍五入保留整数部分
    echo "integer part of 2.38: $(printf "%.0f" 2.38)"
    echo "integer part of 3.49: $(printf "%.0f" 3.49)"
    echo "integer part of 3.5: $(printf "%.0f" 3.5)"
    echo "integer part of 5.9: $(printf "%.0f" 5.9)"
    echo "integer part of 35: $(printf "%.0f" 35)"
    echo "integer part of 43.0: $(printf "%.0f" 43.0)"
}

function main() {
    test_printf_float
}

main
