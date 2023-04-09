#!/bin/bash
CUR_SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${CUR_SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/lib/common.sh

usage() {
    log_info "$0 <url>      using curl download file"
}

function main() {
    if [ $# != 1 ]; then
        usage
        exit
    fi
    local url=$1
    local file=$(basename $url)
    curl -x proxy.nioint.com:8080 $url -o $file
}

main $*
