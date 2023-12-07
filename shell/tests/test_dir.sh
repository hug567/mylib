#!/bin/bash

# 进入目录后回到原目录
function test_entry_dir() {
    echo "$FUNCNAME:-----------------------------"

    echo "PWD = $PWD"

    pushd /tmp/vim > /dev/null
    echo "PWD = $PWD"
    ls -l paste.txt
    popd > /dev/null

    echo "PWD = $PWD"
}

function main() {
    test_entry_dir
}

main
