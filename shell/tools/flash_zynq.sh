#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)

function usage() {
    echo "$0 <bin_file>    flash bin file to zynq qspi flash"
}

function main() {
    if [ "$1" = "-h" ]; then
        usage
        exit 0
    fi
    local bin_file=$1
    local program_flash="/opt/pkg/petalinux/tools/xsct/bin/program_flash"
    local res_dir="/home/hx/temp/flash-zynq"
    local fsbl_file="$res_dir/zynq_fsbl.elf"

    if [ ! -f $bin_file ]; then
        echo "file does not exist: $bin_file"
        exit 1
    fi
    $program_flash -f $bin_file -fsbl $fsbl_file -offset 0 -flash_type qspi-x4-single
}

main $*
