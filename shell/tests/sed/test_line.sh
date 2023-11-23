#!/bin/bash

# 删除头部行
function test_delete_head() {
    echo "$FUNCNAME:-----------------------------"
    local str01=$(ls -l / | head -n 5)
    echo "str01:----------"
    echo "$str01"

    # 删除首行
    local str02=$(echo -n "$str01" | sed '1d')
    echo "str02:----------"
    echo "$str02"
}

function main() {
    test_delete_head
}

main
