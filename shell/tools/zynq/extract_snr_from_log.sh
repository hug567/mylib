#!/bin/bash
# 从日志目录中的modemserver.log日志中提取历史snr，用于绘制曲线
# Create: 2025-03-19 18:18:11

EXTRACT_FILE="history_snr.txt"

function usage() {
    echo "Usage: $0 <dir>        extract snr from modemserver.log"
}

function extract_snr_form_gz_log() {
    local gz_files
    local file

    gz_files="$(ls -1A | grep "^modemserver.log-.*.gz$")"
    if [ "${gz_files}" == "" ]; then
        echo "there is no modemserver.log-*.gz file"
        return
    fi
    echo "${gz_files}" | while read file; do
        echo "will extract history snr from gz file: ${file}"
        cat ${file} | gunzip | grep "get message: C " | awk '{print "data:,"$9}' >> ${EXTRACT_FILE}
    done
}

function extract_snr_form_latest_log() {
    local file="modemserver.log"

    if [ ! -f "${file}" ]; then
        echo "there is no file: ${file}"
        return
    fi
    echo "will extract history snr from file: ${file}"
    cat ${file} | grep "get message: C " | awk '{print "data:,"$9}' >> ${EXTRACT_FILE}
}

function main() {
    local dir=${1}

    if [ $# -ne 1 -o "${1}" == "-h" ]; then
        usage
        exit 1
    fi
    if [ ! -d "${dir}" ]; then
        echo "there is no dir: ${dir}"
        exit 1
    fi
    cd ${dir}
    if [ -f "${EXTRACT_FILE}" ]; then
        echo "will delete old ${EXTRACT_FILE}"
        rm ${EXTRACT_FILE}
    fi
    extract_snr_form_gz_log
    extract_snr_form_latest_log
}

main $*
