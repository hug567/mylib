#!/bin/bash

usage() {
    echo "$1 <file>     line number to function name"
}

if [ $# -ne 1 ]; then
    usage $0
    exit
fi

filename=$1

sed -i 's/^1327$/1327 pl011_stop_tx/g' ${filename}
sed -i 's/^1349$/1349 pl011_start_tx/g' ${filename}
