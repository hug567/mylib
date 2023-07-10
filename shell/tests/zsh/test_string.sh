#!/usr/bin/zsh

function test_split_string() {
    echo "[test_split_string]:-----------------------------"

    echo "[split]: IFS------"
    string="Hello,World,How,Are,You"
    IFS=','
    read -A array <<< "$string"
    for element in "${array[@]}"
    do
        echo "$element"
    done

    echo "[split]: replace------"
    local names="Tom:Bob:Alice"
    local name=("${(@s/:/)names}")
    for n in "${name[@]}"
    do
        echo "$n"
    done
}

function main() {
    test_split_string
}

main
