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
function log_debug()
{
    if [ "$HX_VERBOSE" = "1" ]; then
        echo -e "[$(date +"%Y-%m-%d %H:%M:%S")][D] $*"
    fi
}

function log_info()
{
    echo -e "[$(date +"%Y-%m-%d %H:%M:%S")][${GREEN}I${RESET}] $*"
}

# eg: log_info_var SHELL
function log_info_var()
{
    log_info "$1 = $(eval echo '$'"$1")"
}

function log_warn()
{
    echo -e "[$(date +"%Y-%m-%d %H:%M:%S")][${YELLOW}W${RESET}] $*"
}

function log_error()
{
    echo -e "[$(date +"%Y-%m-%d %H:%M:%S")][${RED}E${RESET}] $*"
}

# eg: check_files_exist file1 file2 ...
function check_files_exist()
{
    for file in $*
    do
        if [ ! -f $file ]; then
            log_error "file $file does not exist"
            exit -1
        fi
    done
}

function check_file_exist()
{
    check_files_exist $*
}

# eg: check_dirs_exist dir1 dir2 ...
function check_dirs_exist()
{
    for dir in $*
    do
        if [ ! -d $dir ]; then
            log_error "dir $dir does not exist"
            exit -1
        fi
    done
}

function check_dir_exist()
{
    check_dirs_exist $*
}

# eg:
#   START_TIME=$(date +%s)
#   END_TIME=$(date +%s)
#   time_diff $END_TIME $START_TIME
function time_diff()
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

function set_shell_runtime() {
    local ret=$(uname -s)
    case "$ret" in
        *Linux*)
            SHELLRUNTIME=Linux
            ;;
        *MINGW64_NT*)
            SHELLRUNTIME=Gitbash
            ;;
        *CYGWIN_NT*)
            SHELLRUNTIME=Mobaxterm
            ;;
        *)
            SHELLRUNTIME=Unknown
            ;;
    esac
    export SHELLRUNTIME
    log_debug "SHELLRUNTIME = $SHELLRUNTIME"
}

function prepare() {
    CPU_THREAD=$(cat /proc/cpuinfo | grep "processor" | wc -l)
    if [ $CPU_THREAD -gt 4 ]; then
        let COMPILE_THREAD=CPU_THREAD-1
    else
        COMPILE_THREAD=$CPU_THREAD
    fi
    export CPU_THREAD COMPILE_THREAD

    set_shell_runtime
}

prepare $*
