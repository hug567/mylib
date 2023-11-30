#!/bin/bash
# 不同进制间的转换

function test_from_decimal() {
    echo "$FUNCNAME:-----------------------------"
    local num=20

    echo "to hexadecimal:-----"
    echo "$num = $(printf 0x%x $num)"
    echo "$num = 0x$(echo "obase=16;$num" | bc)" # default ibase=10

    echo "to octal:-----"
    echo "$num = $(printf 0%o $num)"
    echo "$num = 0$(echo "obase=8;$num" | bc)" # default ibase=10

    echo "to binary:-----"
    echo "$num = $(echo "obase=2;$num" | bc)" # default ibase=10
}

function test_from_hexadecimal() {
    echo "$FUNCNAME:-----------------------------"
    local num=0x14
    local num2=ffff

    echo "to decimal:-----"
    echo "$num = $(printf %d $num)"
    echo "$num = $(($num))"
    echo "0x$num2 = $((0x$num2))"
    echo "0xef = $((0xef))"
    echo "0xff = $((16#ff))"

    echo "to octal:-----"
    echo "$num = $(printf 0%o $num)" # 0x14
    echo "$num = 0$(echo "obase=8;ibase=16;14" | bc)"
    # 16->10->8
    echo "$num = 0$(echo "obase=8;$(($num))" | bc)"
    echo "0xff = 0$(echo "obase=8;$((16#ff))" | bc)"

    echo "to binary:-----"
    echo "$num = $(echo "obase=2;ibase=16;14" | bc)"
    # 16->10->2
    echo "$num = $(echo "obase=2;$(($num))" | bc)"
    echo "0xff = $(echo "obase=2;$((16#ff))" | bc)"
}

function test_from_octal() {
    echo "$FUNCNAME:-----------------------------"
    local num=024

    echo "to hexadecimal:-----"
    echo "$num = $(printf 0x%x $num)"
    echo "$num = 0x$(echo "obase=16;ibase=8;$num" | bc)"
    # 8 -> 10 -> 16
    echo "$num = 0x$(echo "obase=16;$(($num))" | bc)"

    echo "to decimal:-----"
    echo "$num = $(printf %d $num)"
    echo "$num = $(($num))"
    echo "024 = $((024))"
    echo "024 = $((8#24))"

    echo "to binary:-----"
    echo "$num = $(echo "obase=2;ibase=16;14" | bc)"
    echo "$num = $(echo "obase=2;ibase=8;$num" | bc)"
    # 8->10->2
    echo "$num = $(echo "obase=2;$(($num))" | bc)"
    echo "0377 = $(echo "obase=2;$((0377))" | bc)"
}

function test_from_binary() {
    echo "$FUNCNAME:-----------------------------"
    local num=10100

    echo "to hexadecimal:-----"
    echo "$num = 0x$(echo "obase=16;ibase=2;$num" | bc)"

    echo "to decimal:-----"
    echo "$num = $((2#$num))"
    echo "$num = $(echo "obase=10;ibase=2;$num" | bc)"

    echo "to octal:-----"
    echo "$num = 0$(echo "obase=8;ibase=2;$num" | bc)"
}

function main() {
    test_from_decimal
    test_from_hexadecimal
    test_from_octal
    test_from_binary
}

main
