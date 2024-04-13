#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/lib/common.sh

function usage() {
    log_info "$0 <ip> enable      enable iptables forward ip"
    log_info "$0 <ip> disalbe     disable iptables forward ip"
}


function main() {
    if [ $# -ne 2 ]; then
        usage
        exit 1
    fi
    local ip=$1
    local set=$2 # enable / disable
}

main $*
