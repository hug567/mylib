#!/bin/bash
# awk: process the input line by line

function test_awk_normal() {
    echo "$FUNCNAME:-----------------------------"

    local file=/tmp/test_awk.txt
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

function main() {
    test_awk_normal
}

main
