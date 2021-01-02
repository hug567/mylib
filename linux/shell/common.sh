#!/bin/bash
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
PURPLE="\033[35m"
SKYBLUE="\033[36m"
WHITE="\033[37m"
RESET="\033[0m"

CPU_THREAD_NUM=`cat /proc/cpuinfo |grep "processor"|wc -l`

log_info() {
    echo -e "[$SHELL][INFO ] $1"
}

log_error() {
    echo -e "[$SHELL][ERROR] $1"
}

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
