#!/bin/bash

# 进入目录后回到原目录
function test_entry_dir() {
    echo "$FUNCNAME:-----------------------------"

    echo "PWD = $PWD"

    pushd /tmp
    echo "PWD = $PWD"
    ls -l vim_tmp.txt
    popd

    echo "PWD = $PWD"
}

function main() {
    test_entry_dir
}

main
