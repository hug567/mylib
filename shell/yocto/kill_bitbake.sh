#!/bin/bash

START_TIME=$(date +%s)
CUR_SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${CUR_SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/yocto/common.sh

main() {
    local pids=$(ps aux | grep bitbake | grep -v grep | grep -v kill_bitbake | awk '{print$2}')
    echo pids: $pids
    sudo kill -9 $pids
}

main
