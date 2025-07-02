#!/bin/bash

function main() {
    local cur_dir=$(cd $(dirname $BASH_SOURCE[0]); pwd)
    echo "[$0] cur_dir: ${cur_dir}"
}

main $*
