#!/bin/bash
# Copyright (c) 2023 Rhosoon.Co.Ltd. All rights reserved.
# Create: 2023-09-06 09:37:58

LOGFMT="load_fpga"
LOG_DIR="/run/media/mmcblk0p3/logs/latest"
LOG_FILE="$LOG_DIR/load_fpga.log"

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

function main() {
    local fpga_file_dir="/run/media/mmcblk0p3/apps"
    local fpga_file="fpga.bin"
    local firmware_dir="/lib/firmware"

    if [ ! -f "$fpga_file_dir/$fpga_file" ]; then
        log_err "file $fpga_file does not exist"
        exit 1
    fi
    if [ ! -d $firmware_dir ]; then
        log_info "will create dir $firmware_dir"
        mkdir -p $firmware_dir
    fi
    cp $fpga_file_dir/$fpga_file $firmware_dir
    log_info "will load fpga bin file: $fpga_file"
    echo 0 > /sys/class/fpga_manager/fpga0/flags
    echo $fpga_file  > /sys/class/fpga_manager/fpga0/firmware
    log_info "finish load fpga bin file"

    log_info "will enable peripheral power"
    /etc/init.d/enable_power.sh
}

main $*
