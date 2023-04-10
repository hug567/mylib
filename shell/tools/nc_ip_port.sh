#!/bin/bash

function test_port_open() {
    for i in $(seq 0 255)
    do
        local ip=10.110.193.$i
        nc -z -w 3 $ip 1000 # -v: verbose
        if [ $? -eq 0 ]; then
            echo "$ip 1000 port is open"
        fi
    done
}

function main() {
    test_port_open
}

main $*
