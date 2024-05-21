#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../..; pwd)
source ${MYLIB}/shell/lib/common.sh

usage() {
    log_info "$0 <BIN_FILE>         flash bin file to zynq qspi"
}


main() {
    local bin_file=$1
    local program_flash="/opt/pkg/petalinux/tools/xsct/bin/program_flash"

    /opt/pkg/petalinux/tools/xsct/bin/program_flash -f BOOT.BIN -fsbl zynq_fsbl.elf -offset 0 -flash_type qspi-x4-single
}

main $*
