#!/bin/bash

# tee: distribute log to stdout and file
function test_tee() {
    echo "$FUNCNAME:-----------------------------"
    local file=output.txt

    # distribute log to stdout and file
    echo "this is first line" | tee $file
    # tee -a: append to file
    echo "this is second line" | tee -a $file

    echo "file: [$file]"
    cat $file
    rm $file
}

function main() {
    test_tee
}

main
