#!/bin/bash

function usage() {
    echo "Usage: $0 <name>"
    echo "   eg: $0 myubuntu24"
    echo "   eg: $0 myubuntu24.df"
}

function main() {
    local name=$1
    local version="v0.1"

    if [ $# -ne 1 ]; then
        usage
        exit
    fi
    cd "$(cd $(dirname $BASH_SOURCE[0]); pwd)"
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
