#!/bin/bash

CUR_DIR=$(cd $(dirname $0); pwd)
CUR_SOURCE_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd $CUR_SOURCE_DIR/../../..; pwd)
source $MYLIB/linux/shell/common.sh

BUSYBOX_BIN_DIR=
LIB_ROOTFS_DIR=$MYLIB/linux/rootfs

usage() {
    log_info "$0 <busybox _install dir>"
}

parse_args() {
    if [ $# != 1 ]; then
        usage
        exit
    fi
    BUSYBOX_BIN_DIR=$1
    check_dirs_exist $BUSYBOX_BIN_DIR
    check_files_exist $BUSYBOX_BIN_DIR/bin/busybox
    if [ -f bin/busybox ]; then
        log_err "Can not make rootfs in busybox _install dir"
        exit
    fi
}

make_rootfs() {
    if [ -d rootfs ]; then
        sudo rm -rf rootfs
    fi
    mkdir rootfs
    cd rootfs
    cp -rf ${BUSYBOX_BIN_DIR}/* ./

    mkdir -p proc sys tmp root dev/pts etc/init.d usr/bin lib/modules
    cp ${LIB_ROOTFS_DIR}/etc/init.d/rcS etc/init.d/
    cp ${LIB_ROOTFS_DIR}/etc/profile etc/
    chmod a+x etc/init.d/rcS
    chmod a+x etc/profile
    cp ${LIB_ROOTFS_DIR}/etc/passwd etc/

    find . | cpio -o --format=newc > ../rootfs.cpio
    cd ..
    gzip -c rootfs.cpio > rootfs.gzip
}

main() {
    parse_args $*
    make_rootfs
}

main $*
