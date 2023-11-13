#!/bin/bash

function cmd_exist() {
    local cmd=$1

    if which $cmd &> /dev/null; then
        return 0
    else
        return 1
    fi
}

function main() {
    local bin="a.out"

    if cmd_exist qemu-mips; then
        qemu-mipsel -L /usr/mipsel-linux-gnu $bin
    fi
    if cmd_exist qemu-mips-static; then
        qemu-mipsel-static -L /usr/mipsel-linux-gnu $bin
    fi
}

main $*
