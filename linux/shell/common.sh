#!/bin/bash

source $MYLIB/shell/lib/common.sh

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
        cp $src_file $dst_dir
    fi
}

copy_file_to_tmp() {
    copy_file_if_exist $1 tmp
}

copy_file_to_lib_modules() {
    copy_file_if_exist $1 lib/modules
}
