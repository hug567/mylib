#!/bin/bash

function test01() {
    echo "test01:"
    local arr01=(
        "element01"
        "element02"
    )
    for ele in ${arr01[@]}
    do
        echo "element: [$ele]"
    done

    local arr02=(
        element03
        element04
    )
    for ele in ${arr02[@]}
    do
        echo "element: [$ele]"
    done
}

function main() {
    test01
}

main
