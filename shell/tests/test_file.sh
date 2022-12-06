#!/bin/bash

# 逐行读取文件
function read_file_by_line() {
    file=$1
    # 方式一
    while read line
    do
        echo "${line}"
    done < $file

    # 方式二
    cat $file | while read line
    do
        echo "${line}"
    done
}

function main() {
    read_file_by_line /tmp/vim_tmp.txt
}

main
