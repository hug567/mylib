#!/bin/bash
# awk: process the input line by line

function test_awk_normal() {
    echo "$FUNCNAME:-----------------------------"

    local file=/tmp/test_awk.txt

    if [ ! -f ${file} ]; then
        echo "there is no file: ${file}"
        return
    fi

    # the default delimiters are space and tab
    # $1: print the first member after split
    echo "print \$1:-----"
    awk '{print$1}' $file
    # $2: print the second member after split
    echo "print \$2:-----"
    awk '{print$2}' $file
    # $2: print the last member after split
    echo "print \$NF:-----"
    awk '{print$NF}' $file

    # custom FS(delimiter)
    awk -F ':' '{print$2}' $file
}

# 在shell脚本中使用复杂的awk语句
function test_awk_multi() {
    echo "$FUNCNAME:-----------------------------"

    local text=$(ls -l /)
    echo "${text}" | awk '
        {
            size=$5
            if (size > 0) {
                print $0
            }
        }
    '
}

function main() {
    test_awk_normal
    test_awk_multi
}

main
