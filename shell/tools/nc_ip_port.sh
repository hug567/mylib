#!/bin/bash

function test_port_open() {
    for i in $(seq 0 255)
    do
        ip=10.116.36.$i
        echo "ip = $ip"
        timeout 3 nc -z -v $ip 1000
    done
}

function main() {
    test_port_open
}

main $*
