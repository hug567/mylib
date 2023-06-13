#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/lib/common.sh

usage() {
    log_info "$0 <user> <ip> <password> <port> <cmd>        run cmd in remote"
}
#user
#ip
#password
#port
#cmd

function run_cmd_in_remote() {
    local user=$1
    local ip=$2
    local password=$3
    local port=$4
    local cmds="${*:5}"
    local prefix=

    if cmd_exist sshpass && [ "$password" != "none" ]; then
        prefix="sshpass -p $password "
    fi
    $prefix ssh -p$port $user@$ip "$cmds"
}

function main() {
    if [ $# -lt 5 ]; then
        usage
        exit 1
    fi
    run_cmd_in_remote $*
}

main $*



















exit


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
