#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../..; pwd)
source ${MYLIB}/shell/lib/common.sh

function usage() {
    log_info "$0    need run in git dir"
}

function main() {
    local tags=
}

main $*
