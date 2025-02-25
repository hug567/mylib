#!/bin/bash

function usage() {
    echo "usage: $0 <tar file>            unpacking file with show processing"
}

function tar_show_processing() {
    local tar_file=${1}
    local dst_dir=${2}
    local total_size
    local block_size

    total_size=$(gzip -l ${tar_file} | tail -n 1 | awk '{print$1}')
    block_size=$(expr ${total_size} / 51200)
    block_size=$(expr ${block_size} + 1)
    echo "total_size: ${total_size}, block_size: ${block_size}"

    tar --blocking-factor=${block_size} --checkpoint=10 \
        --checkpoint-action='ttyout=unpacking: %u%\n' \
        -xf ${tar_file} -C ${dst_dir}
}

function main() {
    local tar_file=${1}

    if [ $# -ne 1 -o "${1}" == "-h" ]; then
        usage
        exit 1
    fi
    if [ ! -f ${tar_file} ]; then
        echo "there is no file: ${tar_file}"
        exit 1
    fi

    tar_show_processing ${tar_file} ./
}

main $*
