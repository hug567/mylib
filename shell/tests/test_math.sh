#!/bin/bash
# shell math
# 2023.05.06

function test_let() {
    echo "$FUNCNAME:-----------------------------"
    local var1=0
    local var2=0

    let var1+=1
    echo "var1 = $var1"

    let var1=$var1+2
    echo "var1 = $var1"

    var2=5
    let var1=$var1+$var2
    echo "var1 = $var1"
}

# expr加法
function expr_add() {
    echo "$FUNCNAME:-----------------------------"
    local var1=1
    local var2=2

    # immediate add
    echo "1 + 2 = $(expr 1 + 2)"
    echo "1 + 0 = $(expr 1 + 0)"
    echo "1 + -4 = $(expr 1 + -4)"

    # add number in variable
    echo "$var1 + 1 = $(expr $var1 + 1)"
    echo "$var1 + $var2 = $(expr $var1 + $var2)"
}

# expr减法
function expr_sub() {
    echo "$FUNCNAME:-----------------------------"
    local var1=5
    local var2=2

    # immediate sub
    echo "3 - 2 = $(expr 3 - 2)"
    echo "3 - 5 = $(expr 3 - 5)"
    echo "3 - -10 = $(expr 3 - -10)"

    # sub number in variable
    echo "$var1 - 1 = $(expr $var1 - 1)"
    echo "$var1 - $var2 = $(expr $var1 - $var2)"
}

# expr乘法
function expr_mul() {
    echo "$FUNCNAME:-----------------------------"
    local var1=5
    local var2=2

    # immediate multiply
    echo "3 * 2 = $(expr 3 \* 2)"
    echo "3 * 0 = $(expr 3 \* 0)"
    echo "3 * -2 = $(expr 3 \* -2)"

    # multiply number in variable
    echo "$var1 * 5 = $(expr $var1 \* 5)"
    echo "$var1 * $var2 = $(expr $var1 \* $var2)"
}

# expr除法
function expr_div() {
    echo "$FUNCNAME:-----------------------------"
    local var1=5
    local var2=2

    # immediate div
    echo "5 / 2 = $(expr 5 / 2)"
    echo "0 * 2 = $(expr 0 / 2)"
    echo "3 * -2 = $(expr 3 / -2)"

    # div number in variable
    echo "$var1 / 3 = $(expr $var1 / 3)"
    echo "$var1 / $var2 = $(expr $var1 / $var2)"
}

# expr求余
function expr_mod() {
    echo "$FUNCNAME:-----------------------------"
    local var1=5
    local var2=2

    # immediate mod
    echo "5 % 2 = $(expr 5 % 2)"
    echo "0 % 2 = $(expr 0 % 2)"
    echo "3 % -2 = $(expr 3 % -2)"
    echo "-10 % 4 = $(expr -10 % 4)"

    # mod number in variable
    echo "$var1 % 3 = $(expr $var1 % 3)"
    echo "$var1 % $var2 = $(expr $var1 % $var2)"
}

function test_expr() {
    expr_add
    expr_sub
    expr_mul
    expr_div
    expr_mod
}

# 方括号数学计算
function test_square() {
    echo "$FUNCNAME:-----------------------------"

    echo "1 + 2 = $[1 + 2]"
    echo "1 - 2 = $[1 - 2]"
    echo "1 * 2 = $[1 * 2]"
    echo "1 / 2 = $[1 / 2]"
    echo "1 % 2 = $[1 % 2]"
}

# float浮点数计算
function test_bc_float() {
    echo "$FUNCNAME:-----------------------------"

    echo " 1.2 + 3.4 = $(echo "scale=4; 1.2 + 3.4" | bc)"
    echo " 1.2 - 3.4 = $(echo "scale=4; 1.2 - 3.4" | bc)"
    echo " 1.2 * 3.4 = $(echo "scale=4; 1.2 * 3.4" | bc)"
    echo " 321.2 / 3.4 = $(echo "scale=8; 321.2 / 3.4" | bc)"
    echo " 1 / 2 = $(echo "scale=4; 1 / 2" | bc)"
    echo " 3 / 2 = $(echo "scale=4; 3 / 2" | bc)"
}

# 使用awk进行float浮点数计算
function test_awk_float() {
    echo "$FUNCNAME:-----------------------------"

    echo " 3.5 + 2.1 = $(awk 'BEGIN { print 3.5 + 2.1 }')"
    echo " 3.5 - 2.1 = $(awk 'BEGIN { print 3.5 - 2.1 }')"
    echo " 3.5 * 2.1 = $(awk 'BEGIN { print 3.5 * 2.1 }')"
    echo " 3.5 / 2.1 = $(awk 'BEGIN { print 3.5 / 2.1 }')"
    echo " 1 / 2 = $(awk 'BEGIN { print 1 / 2 }')"
    echo " 5 / 3 = $(awk 'BEGIN { print 5 / 3 }')"

    # 向awk中传递shell变量
    local num1=10
    local num2=3
    local ret="$(echo ${num1} ${num2} | awk '{ print $1 / $2 }')"
    echo "$num1 / $num2 = ${ret}"
}

# 双圆括号数学计算: + - * / % ++ -- & | ~ && || << >> **
function test_brackets() {
    echo "$FUNCNAME:-----------------------------"
    local var=

    var=$((1 + 2 * 3 - 4))
    echo "var = $var"

    echo "2^4 = $((2 ** 4))"
}

function main() {
    test_let
    test_expr
    test_square
    test_bc_float
    test_awk_float
    test_brackets
}

main
