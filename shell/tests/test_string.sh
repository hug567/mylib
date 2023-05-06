#!/bin/bash

# 字符串截取
test_string_cut() {
    echo "$FUNCNAME:-----------------------------"
    local str="0123456789"

    # 从左边第2个字符开始截取到末尾，保留第2个字符，下标从0开始
    local s=${str:2}
    echo "s = $s"
}

test_string_length() {
    echo "$FUNCNAME:-----------------------------"
    local str=

    str="123456789"
    echo "string $str length: ${#str}"
    echo "string $str length: $(echo $str | awk '{print length($0)}')"
    echo "string $str length: $(echo $str | awk -F '' '{print NF}')"
    echo "string $str length: $(echo $str | wc -L)"
    echo "string $str length: $(echo -n $str | wc -c)"
    echo "string $str length: $(expr length $str)"
    echo "string $str length: $(expr $str : '.*')"
}

main() {
    test_string_cut
    test_string_length
}

main
