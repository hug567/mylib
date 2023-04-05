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

# export HX_VERBOSE=1
log_debug()
{
    if [ "$HX_VERBOSE" = "1" ]; then
        echo -e "[$(date +"%Y-%m-%d %H:%M:%S")][D] $1"
    fi
}

log_info()
{
    echo -e "[$(date +"%Y-%m-%d %H:%M:%S")][I] $1"
}

# eg: log_info_var SHELL
log_info_var()
{
    log_info "$1 = $(eval echo '$'"$1")"
}

log_error()
{
    echo -e "[$(date +"%Y-%m-%d %H:%M:%S")][E] $1"
}

# eg: check_files_exist file1 file2 ...
check_files_exist()
{
    for file in $*
    do
        if [ ! -f $file ]; then
            log_error "file $file does not exist"
            exit -1
        fi
    done
}

check_file_exist()
{
    check_files_exist $*
}

# eg: check_dirs_exist dir1 dir2 ...
check_dirs_exist()
{
    for dir in $*
    do
        if [ ! -d $dir ]; then
            log_error "dir $dir does not exist"
            exit -1
        fi
    done
}

check_dir_exist()
{
    check_dirs_exist $*
}

# eg:
#   START_TIME=$(date +%s)
#   END_TIME=$(date +%s)
#   time_diff $END_TIME $START_TIME
time_diff()
{
    end_time=$1
    start_time=$2
    diff_s=$(( $end_time - $start_time ))
    hour=$(( $diff_s / 3600 ))
    min=$(( ($diff_s - $hour * 3600) / 60 ))
    second=$(( $diff_s - ($hour * 3600) - ($min * 60) ))
    printf "%02d:%02d:%02d" $hour $min $second
}

function task_is_finished() {
    task=$1
    ret=$(ps | grep $task | grep -v "grep")
    if [ "$ret" = "" ]; then
        return 0 # true
    else
        return 1 # false
    fi
}

function task_is_running() {
    task=$1
    ret=$(ps | grep $task | grep -v "grep")
    if [ "$ret" != "" ]; then
        return 0 # true
    else
        return 1 # false
    fi
}

function wait_task_finish() {
    task=$1
    while true; do
        if task_is_finished $task; then
            return
        else
            sleep 1
        fi
    done
}

prepare() {
    CPU_THREAD=$(cat /proc/cpuinfo | grep "processor" | wc -l)
    if [ $CPU_THREAD -gt 4 ]; then
        let COMPILE_THREAD=CPU_THREAD-1
    else
        COMPILE_THREAD=$CPU_THREAD
    fi
    export CPU_THREAD COMPILE_THREAD
}

prepare $*
