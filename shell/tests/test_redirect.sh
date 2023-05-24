#!/bin/bash

# 0: STDIN
# 1: STDOUT
# 2: STDERR
# 3-8: shell can be customized to use

function test_temp_redirect() {
    echo "$FUNCNAME:-----------------------------"
    local file="output.txt"
    local file2="output2.txt"

    # redirect STDOUT to file
    ls -l > $file
    cat $file; rm $file

    # only redirect STDERR to file
    ls xxx 2> $file
    echo "$file:"; cat $file; rm $file

    # redirect STDOUT and STDERR to /dev/null
    ls xxx > /dev/null 2>&1

    # redirect STDOUT and STDERR to different file
    ls -l $0 xxx 1> $file 2> $file2
    echo "$file:"; cat $file; rm $file
    echo "$file2:"; cat $file2; rm $file2

    # redirect STDOUT and STDERR to same file
    ls -l $0 xxx &> $file # /dev/null
    echo "$file:"; cat $file; rm $file

    # redirect STDOUT and STDERR to /dev/null
    ls xxx > /dev/null 2>&1
    ls xxx &> /dev/null

    # redirect STDOUT to STDERR
    echo "This is an error message" >&2
}

function test_perm_redirect() {
    echo "$FUNCNAME:-----------------------------"
    local file="output.txt"

    # backup STDOUT and STDERR to 6/7
    exec 6<&0
    exec 7<&1

    #exec 1>$file
    #exec 2>$file
    # permanently redirect STDOUT and STDERR to same file
    exec &> $file
    ls -l $0 xxx

    # restore STDOUT and STDERR from 6/7
    exec 0<&6
    exec 1<&7

    echo "$file:"; cat $file ; rm $file

    # close fd
    exec 6>&-
    exec 7>&-
}

function test_create_output_fd() {
    echo "$FUNCNAME:-----------------------------"
    local file="output.txt"

    # create fd and redirect to file
    exec 3>$file
    echo "this is first line" >&3
    echo "this is second line" >&3
    echo "$file:"; cat $file ; rm $file

    # close fd
    exec 3>&-
}

function test_create_input_fd() {
    echo "$FUNCNAME:-----------------------------"
    local file="input.txt"

    echo "this is line 1" > $file
    echo "this is line 2" >> $file

    # backup
    exec 6<&0

    exec 0<$file
    local i=1
    while read line; do
        echo "line $i: [$line]"
        let i++
    done

    # restore
    exec 0<&6
    # close fd
    exec 6>&-

    rm $file
}

function main() {
    test_temp_redirect
    test_perm_redirect
    test_create_output_fd
    test_create_input_fd
}

main
