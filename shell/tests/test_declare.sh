#!/bin/bash

function test_declare_int() {
    echo "$FUNCNAME:-----------------------------"

    # - : give attribute
    declare -i local var01
    var01=123
    echo "var01: $var01"

    # + : clear arrribute
    declare +i var01
    var01="hello"
    echo "var01: $var01"
}

function test_declare_readonly() {
    echo "$FUNCNAME:-----------------------------"

    declare -r local name="Bob"
    echo "name: $name"
    # name="Tom"  # cannot change name value
}

function test_declare_array() {
    echo "$FUNCNAME:-----------------------------"

    declare -a local names=(
        [0]="Bob"
        [1]="Tom"
        [2]="Jerry"
    )
    echo "names: ${names[@]}"
}

function test_declare_dictionary() {
    echo "$FUNCNAME:-----------------------------"

    declare -A local stu2=(
        ['name']=Tom
        ['age']=19
    )
    echo "stu2 name: ${stu2['name']}, age: ${stu2['age']}"
}

function main() {
    test_declare_int
    test_declare_readonly
    test_declare_array
    test_declare_dictionary
}

main
