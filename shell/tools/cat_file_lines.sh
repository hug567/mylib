#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/lib/common.sh

usage() {
    log_info "$0 <file> <start>          dump file line <start> to last column"
    log_info "$0 <file> <start> <line>   dump file line <start> with <line>"
}


main() {
    if [ $# -lt 2 -o $# -gt 3 ]; then
        usage
        exit 1
    fi
    local file=$1
    local start_line=$2
    local line_num=$3
    local end_line=
    local file_line=

    check_files_exist $file
    file_line=$(wc -l $file | awk -F ' ' '{print$1}')
    if [ $start_line -gt $file_line ]; then
        log_error "start line $start_line is larger then file line $file_line"
        exit 2
    fi

    if [ "${line_num}" = "" ]; then
        end_line=$file_line
    else
        let end_line=$start_line+$line_num
    fi

    if [ $start_line -gt $end_line ]; then
        log_error "start line $start_line is larger then end line $end_line"
        exit 3
    fi

    if [ $end_line -gt $file_line ]; then
        end_line=$file_line
    fi

    let line_num=$end_line-$start_line
    let line_num=$line_num+1
    head -n $end_line $file | tail -n $line_num
}

main $*
