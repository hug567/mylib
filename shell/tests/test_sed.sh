#!/bin/bash

function test_sed_replace() {
    echo "$FUNCNAME:-----------------------------"

    local str01="1234567890"
    local str02=$(echo $str01 | sed 's/456/xxx/g')
    echo "str01: $str01"
    echo "str02: $str02"

    local str01="1234567890xx%20yy"
    local str02=$(echo $str01 | sed 's/%20/_/g')
    echo "str01: $str01"
    echo "str02: $str02"
}

function main() {
    test_sed_replace
}

main
