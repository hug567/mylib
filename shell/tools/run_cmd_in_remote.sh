#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/lib/common.sh

usage() {
    log_info "$0 <user> <ip> <password> <port> <cmd>        run cmd in remote"
}

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
