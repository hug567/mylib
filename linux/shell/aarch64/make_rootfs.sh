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

_install_file() {
    local file=$1
    local dst=$2
    if [ ! -f $file ]; then
        echo "$file does not exist"
        exit 1
    fi
    if [ ! -d $dst ]; then
        echo "dst dir $dst does not exist"
        exit 1
    fi
    echo "install $file to $dst"
    install $file $dst
}

_install_to_lib() {
    _install_file $1 lib
}

_install_to_etc() {
    _install_file $1 etc
}

install_libc() {
    local root_dir=$1
    local libc_dir=$(dirname $(which aarch64-linux-gnu-gcc))/../aarch64-linux-gnu/libc/lib
    local lib_files=(
        ld-2.25.so
        ld-linux-aarch64.so.1
        libc.so.6
        libc-2.25.so
        libdl.so.2
        libdl-2.25.so
        libutil.so.1
        libutil-2.25.so
        libresolv.so.2
        libresolv-2.25.so
    )
    for file in ${lib_files[@]}; do
        _install_to_lib $libc_dir/$file
    done
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
    #cp ${src}/moduli      ${dst}/usr/etc
    #cp ${src}/ssh_config  ${dst}/usr/etc
    #cp ${src}/sshd_config ${dst}/usr/etc
    cp ${src}/sftp-server ${dst}/usr/libexec
    cp ${src}/ssh-keysign ${dst}/usr/libexec
}

install_tmp_files() {
    local root_dir=$1
    local dst_dir=$root_dir/tmp
    local tmp_dir="/tmp/rootfs-aarch64"
    if [ ! -d $tmp_dir ]; then
        return
    fi
    for file in $tmp_dir/*; do
        echo "copy $file to $dst_dir"
        cp -r $file $dst_dir
    done
}

install_base_file() {
    cp -rf ${BUSYBOX_BIN_DIR}/* ./

    mkdir -p proc sys tmp root dev/pts etc/init.d usr/bin lib/modules usr/local/bin
    cp ${LIB_ROOTFS_DIR}/etc/init.d/rcS etc/init.d/
    cp ${LIB_ROOTFS_DIR}/etc/profile etc/
    chmod a+x etc/init.d/rcS
    chmod a+x etc/profile
    cp ${LIB_ROOTFS_DIR}/etc/passwd etc/

    #_install_to_etc $LIB_ROOTFS_DIR/etc/inittab
}

make_rootfs() {
    rm -rf rootfs rootfs.cpio rootfs.cpio.gz
    mkdir rootfs
    cd rootfs

    install_base_file
    install_libc $(pwd)
    install_tmp_files $(pwd)
    #install_zlib /home/hx/code/others/zlib-1.2.13/build-aarch64/install $PWD
    #install_openssl /home/hx/code/others/openssl-3.1.0/build-aarch64/install $PWD
    #install_openssh /home/hx/code/others/openssh-9.3p1/build-aarch64 $PWD

    find . | cpio -o --format=newc > ../rootfs.cpio
    cd ..
    gzip -c rootfs.cpio > rootfs.cpio.gz
}

main() {
    parse_args $*
    make_rootfs
}

main $*
