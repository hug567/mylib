#!/bin/bash

function usage() {
    echo "Usage: $0 <name>"
    echo "   eg: $0 myubuntu24"
}

function main() {
    local name=$1

    if [ $# -ne 1 ]; then
        usage
        exit
    fi
    if [ ! -f ${name}.df ]; then
        echo "there is no file: ${name}.df"
        exit
    fi
    docker build -t ${name}:v0.1 -f ${name}.df ./
}

main $*
