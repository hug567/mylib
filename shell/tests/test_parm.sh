#!/bin/bash

# 传递带空格的参数
function test_para_with_space() {
    para1="$1"
    echo "para1: [$para1]"
}

# 逐个遍历参数
function traverse_param() {
    # 参数个数
    echo "param num: $#"
    # 遍历参数
    i=1
    for p in $*
    do
        echo "param $i: $p"
        let i=i+1
    done
}

function main() {
    test_para_with_space " 123 "
    traverse_param p1 q2 r3 s4
}

main
