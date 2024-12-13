#!/bin/bash

function usage() {
    echo "Usage: $0 <start> <num>        print reg/mem val from start addr"
    echo "   eg: $0 0x3c000000 16"
}

function main() {
    if [ $# != 2 ]; then
        usage
        exit 1
    fi
    local start=$1
    local num=$2
    local i=0
    let num=num-1
    for i in $(seq 0 $num); do
        addr=$(printf 0x%x $(expr $(($start)) + $i \* 4))
        val=$(peek $addr)
        echo "[$addr] = $val"
    done
}

main $*
