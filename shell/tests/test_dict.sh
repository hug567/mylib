#!/bin/bash
# learning shell dictionary
# 2023-05-30

function test_dict() {
    echo "$FUNCNAME:-----------------------------"

    # define dictionary
    declare -A local stu
    # assign value
    stu['name']=Bob
    stu['age']=18
    # use
    echo "student name: ${stu['name']}, age: ${stu['age']}"

    # assign value when defile
    declare -A local stu2=(
        ['name']=Tom
        ['age']=19
    )
    echo "stu2 name: ${stu2['name']}, age: ${stu2['age']}"
}

function test_dict_traverse() {
    echo "$FUNCNAME:-----------------------------"

    declare -A local files=(
        ['name']='test.txt'
        ['size']=1024
        ['cerate']=20230530
    )
    # traverse dictionary
    for key in $(echo ${!files[*]}); do
        echo "file $key: ${files[$key]}"
    done
}

function main() {
    test_dict
    test_dict_traverse
}

main
