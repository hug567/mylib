#!/bin/bash

function usage() {
    echo "Usage: ${0} <start> <internal> <end>       git fetch with depth"
    echo "   eg: ${0} 0 100 11000"
}

function main() {
    local start=${1}
    local internal=${2}
    local end=${3}
    local cur=${start}

    if [ $# -ne 3 ]; then
        usage
        exit
    fi
    while true; do
        echo "[INFO]: ---------------------------------------------------------"
        echo "[INFO]: git fetch --depth=${cur}"
        git fetch --depth=${cur}
        if [ $? -ne 0 ]; then
            echo "[ERROR]: git fetch --depth=${cur} failed"
            exit
        fi
        if [ ${cur} -gt ${end} ]; then
            break
        fi
        let cur=cur+internal
    done
}

main $*
