#!/bin/bash

function test_mktemp() {
    echo "$FUNCNAME:-----------------------------"
    local file=
    local dir=

    # create temp file in current dir
    file=$(mktemp temp_file.XXXXXX)
    echo "file: $file"
    ls -l $file
    rm $file

    # create temp dir in current dir
    dir=$(mktemp -d temp_dir.XXXXXX)
    echo "dir: $dir"
    ls -l | grep $dir
    rm -r $dir

    # create temp file in /tmp dir
    file=$(mktemp -t temp_file.XXXXXX)
    echo "file: $file"
    ls -l $file
    rm $file

    # create temp dir in /tmp dir
    dir=$(mktemp -t -d temp_dir.XXXXXX)
    echo "dir: $dir"
    ls -l /tmp | grep $(echo $dir | awk -F '/' '{print$NF}')
    rm -r $dir
}

function main() {
    test_mktemp
}

main
