#!/bin/bash

function main() {
    local dir=/home/root/share
    if [ ! -d $dir ]; then
        mkdir -p $dir
    fi
    mount -t nfs -o nolock,vers=3 192.168.0.13:/home/hx/share /home/root/share/
}

main $*
