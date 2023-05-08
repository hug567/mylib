#!/bin/bash
# shell逻辑运算
#   与：-a / &&
#   或：-o / ||
#   非：!
#   -a/-o用在单方括号中，&&/||用在双方括号中或单方括号外部

# 逻辑与
function test_and() {
    echo "$FUNCNAME:-----------------------------"
    para1=1
    para2=2
    if [ "$para1" = "1" -a "$para2" = "2" ]; then
        echo "para1 is 1 and para2 is 2"
    fi

    para1=3
    para2=4
    if [[ "$para1" = "3" && "$para2" = "4" ]]; then
        echo "para1 is 3 and para2 is 4"
    fi
    # outside a single square bracket
    if [ $para1 -eq 3 ] && [ $para2 -eq 4 ]; then
        echo "para1 is 3 and para2 is 4"
    fi
}

# 逻辑或
function test_or() {
    echo "$FUNCNAME:-----------------------------"
    para1=1
    para2=3
    if [ "$para1" = "1" -o "$para2" = "2" ]; then
        echo "para1 is 1 or para2 is 2"
    fi

    para1=5
    para2=4
    if [[ "$para1" = "3" || "$para2" = "4" ]]; then
        echo "para1 is 3 or para2 is 4"
    fi
    # outside a single square bracket
    if [ $para1 -eq 3 ] || [ $para2 -eq 4 ]; then
        echo "para1 is 3 or para2 is 4"
    fi
}

# 逻辑非
function test_not() {
    echo "$FUNCNAME:-----------------------------"
    para1=1
    if [ ! $para1 -eq 2 ]; then
        echo "para1 is not 2"
    fi
}

function main() {
    test_and
    test_or
    test_not
}

main
