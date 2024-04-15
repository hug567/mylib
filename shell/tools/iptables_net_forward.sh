#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/lib/common.sh

function usage() {
    log_info "$0 enable <inside_ip> <outside_ip>      enable iptables forward inside ip"
    log_info "$0 disalbe <inside_ip>                  disable iptables forward inside ip"
}

function delete_ip_forward() {
    local ip=$1
}

function add_ip_forward() {
    local ip=$1
}

function main() {
    if [ "$1" = "-h" ]; then
        usage
        exit 0
    fi
    if [ $# -lt 2 -o $# -gt 3 ]; then
        usage
        exit 1
    fi
    local set=$1 # enable / disable
    local inside_ip=$2
    local outside_ip=$3
}

main $*
