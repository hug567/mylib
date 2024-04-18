#!/bin/bash

function test_array() {
    echo "$FUNCNAME:-----------------------------"
    # define array
    local arr01=(
        "element01"
        "element02"
    )
    for ele in ${arr01[@]}; do
        echo "element: [$ele]"
    done

    # define array
    local arr02=(
        element11
        element12
    )
    # traverse array
    for ele in ${arr02[@]}; do
        echo "element: [$ele]"
    done
    # all elements of array
    echo "all elements: ${arr02[*]}"
    echo "all elements: ${arr02[@]}"
    # array length
    echo "array length: ${#arr02[*]}"
    echo "array length: ${#arr02[@]}"

    # assign member one by one
    local arr03[0]="element30"
    local arr03[1]="element31"
    local arr03[2]="element32"
    # access member one by one
    for (( i = 0; i < 3; i++ )); do
        echo "arr03[$i] = ${arr03[$i]}"
    done
}

function test_array_delete() {
    echo "$FUNCNAME:-----------------------------"

    local arr=(0 1 2 3 4 5)
    echo "arr: ${arr[@]}"
    # delete the specified element, index starts at 0
    unset arr[2]
    echo "arr: ${arr[@]}"
    # clear array
    unset arr
    echo "arr: ${arr[@]}"
}

function test_array_local_access() {
    echo "$FUNCNAME:-----------------------------"

    local arr=(0 1 2 3 4 5)
    # starts at index 1, total of 3 elements are accessed
    echo "arr[1-3]: ${arr[@]:1:3}"
}

# shell dictionary
function test_associated_array() {
    echo "$FUNCNAME:-----------------------------"

    # define associated array
    declare -A stu=(
        ["name"]="Bob"
        ["age"]=18
        ["height"]=175
    )
    # access associated array element
    echo "student name: ${stu["name"]}"
    echo "student age: ${stu["age"]}"
    echo "student height: ${stu["height"]}"

    # define associated array
    declare -A stu2
    stu2["name"]="Tom"
    stu2["age"]=19
    stu2["height"]=176
    # access associated array element
    echo "student name: ${stu2["name"]}"
    echo "student age: ${stu2["age"]}"
    echo "student height: ${stu2["height"]}"
}

function test_array_append() {
    echo "$FUNCNAME:-----------------------------"

    # define empty array
    local arr01=()
    echo "array size: ${#arr01[@]}"

    # append to array tail
    arr01+=("Tom")
    arr01+=("Bob")
    echo "array size: ${#arr01[@]}"
}

# 二维数组：使用一维数组模拟二维数组
function test_two_dim_array() {
    echo "$FUNCNAME:-----------------------------"

    local i=
    local j=
    local index_0=
    local index_1=
    local index_2=
    local arr=(
      1 2 3
      4 5 6
      7 8 9
      3 5 8
    )
    local len=${#arr[@]}
    local col_num=3
    local row_num=$(expr $len / $col_num)
    echo "len: $len, row_num: $row_num"

    for (( i = 0; i < $row_num; i++ )); do
        echo "arr line $i: ----------"
        index_0=$(expr $i \* $col_num + 0)
        index_1=$(expr $i \* $col_num + 1)
        index_2=$(expr $i \* $col_num + 2)
        echo "arr[$i][0]: ${arr[$index_0]}"
        echo "arr[$i][1]: ${arr[$index_1]}"
        echo "arr[$i][2]: ${arr[$index_2]}"
    done
}

function main() {
    test_array
    test_array_delete
    test_array_local_access
    test_associated_array
    test_array_append
    test_two_dim_array
}

main
