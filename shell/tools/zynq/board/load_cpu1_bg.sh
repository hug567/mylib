#!/bin/bash
# Copyright (c) 2023 Rhosoon.Co.Ltd. All rights reserved.
# Create: 2023-09-22 10:20:03

LOGFMT="load_cpu1"
LOG_DIR="/run/media/mmcblk0p3/logs/latest"
LOG_FILE="$LOG_DIR/load_cpu1.log"
MAX_WAIT_COUNT=10000

function log_with_level() {
    local level=$1
    local logs=${@:2}

    echo -e "[$(date '+%Y-%m-%d %H:%M:%S')][$LOGFMT][$level] $logs"
    echo -e "[$(date '+%Y-%m-%d %H:%M:%S')][$LOGFMT][$level] $logs" >> $LOG_FILE
}

function log_info() {
    log_with_level "INFO" $*
}

function log_warn() {
    log_with_level "WARN" $*
}

function log_err() {
    log_with_level "ERROR" $*
}

function set_config_from_json() {
    sleep 5
    log_info "will set config from json"
    configset -f >> $LOG_FILE
    if [ $? -ne 0 ]; then
        log_err "set config from json failed"
        exit 1
    fi
    log_info "set config from json success"
}

function main() {
    local cpu1_file="/run/media/mmcblk0p3/apps/cpu1.bin"

    if [ ! -f "$cpu1_file" ]; then
        log_err "file $cpu1_file does not exist"
        exit 1
    fi

    local flag_file="/run/media/mmcblk0p3/not_load_cpu1"
    if [ -f ${flag_file} ]; then
        log_warn "[hx-debug] will not load cpu1.bin"
        exit 1
    fi
    touch ${flag_file}
    sync

    log_info "will load cpu1 bin file: $cpu1_file"
    load_cpu1 $cpu1_file >> $LOG_FILE
    if [ $? -ne 0 ]; then
        log_err "load cpu1 bin file failed"
        exit 1
    fi
    log_info "load cpu1 bin file success"
    set_config_from_json
}

main $*
