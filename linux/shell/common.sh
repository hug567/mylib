#!/bin/bash

source ${MYLIB}/shell/lib/common.sh

copy_file() {
    src_file=$1
    dst_dir=$2
    if [ ! -f $src_file ]; then
        log_error "[$src_file] does not exist"
        exit
    fi
    if [ ! -d $dst_dir ]; then
        log_error "[$dst_dir] does not exist"
        exit
    fi
    cp $src_file $dst_dir
}

copy_file_if_exist() {
    src_file=$1
    dst_dir=$2
    if [[ -f $src_file && -d $dst_dir ]]; then
        log_info "copy [$src_file] to [$dst_dir]"
        cp -rd $src_file $dst_dir
    fi
}

copy_file_to_tmp() {
    copy_file_if_exist $1 tmp
}

copy_file_to_lib() {
    copy_file_if_exist $1 lib
}

copy_file_to_lib_modules() {
    copy_file_if_exist $1 lib/modules
}

check_in_build_dir()
{
    build_dir=$(expr substr $(echo $PWD | sed "s/\// /g" | awk 'NR=1{print $NF}') 1 6)
    if [[ "$build_dir" != "build-" ]]; then
        log_error "Currently not in build dir"
        exit
    fi
    if [ ! -f ${PWD}/../include/linux/kernel.h ]; then
        log_error "Currently not in linux kernel build dir"
        exit
    fi
}
