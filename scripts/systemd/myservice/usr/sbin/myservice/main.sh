#!/bin/bash

LOGFMT="myservice"

function log_with_level() {
    local level=$1
    local logs="${@:2}"

    echo -e "[$(date '+%Y-%m-%d %H:%M:%S')][$LOGFMT][$level] $logs"
}

function log_info() {
    log_with_level "INFO" "$*"
}

function log_warn() {
    log_with_level "WARN" "$*"
}

function log_err() {
    log_with_level "ERROR" "$*"
}

function main() {
    log_info "Enter $0"
}

main $*
