#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/lib/common.sh

function usage() {
    log_info "$0 <url>          git clone repo by proxy"
}

function main() {
    if [ $# != 1 ]; then
        usage
        exit 1
    fi
    local url=$1

    ./clash &
    sleep 3
    #export http_proxy="http://127.0.0.1:7890"
    #export https_proxy="http://127.0.0.1:7890"
    git clone -c http.proxy="http://127.0.0.1:7890" $url
}

main $*
