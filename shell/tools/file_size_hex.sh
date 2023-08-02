#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/lib/common.sh

function usage() {
    log_info "$0 <file>         Displays file size in hexadecimal"
}

function main() {
    local file=$1
    local size_dec=
    local size_hex=

    if [ $# != 1 -o ! -f $file  ]; then
        usage
        exit 1
    fi
    ls -l $file
    size_dec=$(ls -l $file | awk '{print$5}')
    size_hex=$(printf %x $size_dec)
    echo "[$file] size: $size_dec / 0x$size_hex"
}

main $*
