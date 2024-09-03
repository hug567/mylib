#!/bin/bash

# sed按行删除
# 直接操作文件：sed -i <...> <file>
function test_delete_line() {
    echo "$FUNCNAME:-----------------------------"
    local str01=$(ls -l / | grep -v "total" | head -n 5)
    echo "str01:----------"
    echo "$str01"

    # 删除首行
    local str02=$(echo -n "$str01" | sed '1d')
    echo "str02:----------"
    echo "$str02"

    # 删除1-3行
    local str03=$(echo -n "$str01" | sed '1,3d')
    echo "str03:----------"
    echo "$str03"

    # 删除第3行
    local str04=$(echo -n "$str01" | sed '3d')
    echo "str04:----------"
    echo "$str04"

    # 删除最后行
    local str05=$(echo -n "$str01" | sed '$d')
    echo "str05:----------"
    echo "$str05"

    # 删除含有指定字符串的行: "dev"
    local str06=$(echo -n "$str01" | sed '/dev/d')
    echo "str06:----------"
    echo "$str06"
}

function main() {
    test_delete_line
}

main
