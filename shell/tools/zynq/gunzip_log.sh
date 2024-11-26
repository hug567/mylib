#!/bin/bash

function usage() {
    echo "Usage: $0 <dir>      gunzip all gz log file"
}

function gunzip_logs() {
    local log_dir=${1}
    local output_dir="gunzip_log"
    local all_gz_logs
    local log_fname
    local gunzip_fname

    pushd ${log_dir}
    if [ ! -d ${output_dir} ]; then
        mkdir ${output_dir}
    fi
    all_gz_logs=$(ls -1 *.log*.gz)
    if [ "${all_gz_logs}" == "" ]; then
        echo "there is no gz log file"
        return
    fi
    echo "${all_gz_logs}" | while read log_fname; do
        gunzip_fname="${log_fname%.*}.log"
        echo "will gunzip gz log file: ${log_fname} to ${output_dir}/${gunzip_fname}"
        cat ${log_fname} | gunzip > ${output_dir}/${gunzip_fname}
    done
    popd
}

function main() {
    local log_dir=$1

    if [ $# -ne 1 -o "${log_dir}" == "-h" ]; then
        usage
        exit 1
    fi
    if [ ! -d "${log_dir}" ]; then
        echo "there is no dir: ${log_dir}"
        eixt 1
    fi
    gunzip_logs ${log_dir}
}

main $*
