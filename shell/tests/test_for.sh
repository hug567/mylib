#!/bin/bash

function test_for_loop() {
    echo "$FUNCNAME:-----------------------------"

    local students="Bom Tom Alice"
    # traverse the list, the default delimiter is space, \t and \n
    for stu in $students; do
        echo "student: $stu"
    done

    # custom delimiter: IFS
    IFS_OLD=$IFS
    IFS=$','
    local cityes="Hei Fei,Nan Jing,Shang Hai"
    for city in $cityes; do
        echo "city: $city"
    done
    IFS=$IFS_OLD
}

function test_for_loop_files() {
    echo "$FUNCNAME:-----------------------------"

    # traverse all files in the current directory
    for file in ./*; do
        echo "file: $file"
    done
}

function test_for_array() {
    echo "$FUNCNAME:-----------------------------"
    local i=

    for i in $(seq 0 9); do
        echo "i = $i"
    done

    # c language style for loop
    for (( i = 10; i < 20; i++ )); do
        echo "i = $i"
    done
}

function test_for_output_redirection() {
    echo "$FUNCNAME:-----------------------------"
    local i=

    for (( i = 10; i < 20; i++ )); do
        echo "[$FUNCNAME] i = $i"
    done >> for_output.txt  # output redirection
    ls -l for_output.txt
    cat for_output.txt
    rm -rf for_output.txt

    for (( i = 10; i >= 0; i-- )); do
        echo "[sort] i = $i"
    done | sort  # output to pipe
}

function main() {
    test_for_loop
    test_for_loop_files
    test_for_array
    test_for_output_redirection
}

main
