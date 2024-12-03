#!/bin/bash

function usage() {
    echo "Usage: $0 <name>"
    echo "   eg: $0 myubuntu18"
    echo "   eg: $0 myubuntu18.df"
}

function main() {
    local name=$1
    local version="v0.1"

    if [ $# -ne 1 ]; then
        usage
        exit
    fi
    if [[  "${name}" =~ .*\.df$ ]]; then
        name=$(echo "${name}" | sed 's/\(.*\)\.df$/\1/g')
    fi
    if [ ! -f ${name}.df ]; then
        echo "there is no file: ${name}.df"
        exit
    fi
    echo "will build ${name}:${version} by ${name}.df"
    docker build -t ${name}:${version} -f ${name}.df ./
}

main $*
