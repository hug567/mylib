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

install_zlib() {
    local src=$1
    local dst=$2

    check_dirs_exist $src $dst
    check_files_exist $src/lib/libz.a
    cp -r $src/* $dst
}

install_openssl() {
    local src=$1
    local dst=$2

    check_dirs_exist $src $dst
    check_files_exist $src/bin/openssl
    cp -r $src/* $dst
}

install_openssh() {
    local src=$1
    local dst=$2

    check_dirs_exist $src $dst
    check_files_exist $src/ssh

    if [ ! -d $dsr/usr/local/bin ]; then
        mkdir -p $dsr/usr/local/bin
    fi
    if [ ! -d $dsr/usr/local/etc ]; then
        mkdir -p $dsr/usr/local/etc
    fi
    if [ ! -d $dsr/usr/libexec ]; then
        mkdir -p $dsr/usr/local/libexec
    fi
    cp ${src}/scp         ${dst}/usr/bin
    cp ${src}/sftp        ${dst}/usr/bin
    cp ${src}/ssh         ${dst}/usr/bin
    cp ${src}/sshd        ${dst}/usr/bin
    cp ${src}/ssh-add     ${dst}/usr/bin
    cp ${src}/ssh-agent   ${dst}/usr/bin
    cp ${src}/ssh-keygen  ${dst}/usr/bin
    cp ${src}/ssh-keyscan ${dst}/usr/bin
    cp ${src}/moduli      ${dst}/usr/etc
    cp ${src}/ssh_config  ${dst}/usr/etc
    cp ${src}/sshd_config ${dst}/usr/etc
    cp ${src}/sftp-server ${dst}/usr/libexec
    cp ${src}/ssh-keysign ${dst}/usr/libexec
}

make_rootfs() {
    if [ -d rootfs ]; then
        sudo rm -rf rootfs
    fi
    mkdir rootfs
    cd rootfs
    cp -rf ${BUSYBOX_BIN_DIR}/* ./

    mkdir -p proc sys tmp root dev/pts etc/init.d usr/bin lib/modules usr/local/bin
    cp ${LIB_ROOTFS_DIR}/etc/init.d/rcS etc/init.d/
    cp ${LIB_ROOTFS_DIR}/etc/profile etc/
    chmod a+x etc/init.d/rcS
    chmod a+x etc/profile
    cp ${LIB_ROOTFS_DIR}/etc/passwd etc/

    install_zlib /home/hx/code/others/zlib-1.2.13/build-aarch64/install $PWD
    install_openssl /home/hx/code/others/openssl-3.1.0/build-aarch64/install $PWD
    install_openssh /home/hx/code/others/openssh-9.3p1/build-aarch64 $PWD

    find . | cpio -o --format=newc > ../rootfs.cpio
    cd ..
    gzip -c rootfs.cpio > rootfs.gzip
}

main() {
    parse_args $*
    make_rootfs
}

main $*
