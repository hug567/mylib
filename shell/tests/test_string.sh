#!/bin/bash

# 字符串截取
test_string_cut() {
    echo "$FUNCNAME:-----------------------------"
    local str="0123456789"

    # 从左边第2个字符开始截取到末尾，保留第2个字符，下标从0开始
    local s=${str:2}
    echo "s = $s"
}

main() {
    test_string_cut
}

main
