#!/bin/bash
# 在某个机器上使用crontab定期执行的脚本的例子

LOGFMT="mycrontab"
LOGFILE="/tmp/mycrontab.log"

function log_with_level() {
    local level=$1
    local logs="${@:2}"

    echo -e "[$(date '+%Y-%m-%d %H:%M:%S')][$LOGFMT][$level] $logs"
    echo -e "[$(date '+%Y-%m-%d %H:%M:%S')][$LOGFMT][$level] $logs" >> ${LOGFILE}
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

function not_get_intranet_dhcp() {
    local dev=$1
    local ip="192.168.99"
    local ret=

    ret=$(ip a show dev ${dev} | grep "${ip}")
    if [ "${ret}" == "" ]; then
        return 0
    fi
    return 1
}

function set_ip_to_dev() {
    local dev=$1
    local ip=$2
    local ret=

    ret=$(ip a show dev ${dev} | grep "${ip}")
    if [ "${ret}" == "" ]; then
        log_info "will add static ip ${ip} to dev ${dev}"
        ip addr add dev ${dev} ${ip}/24
    fi
}

function set_static_ip() {
    local dev="eno1"

    if not_get_intranet_dhcp ${dev}; then
        return
    fi
    set_ip_to_dev ${dev} "10.110.0.3"
    set_ip_to_dev ${dev} "192.168.0.13"
}

function main() {
    export PATH="$PATH:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
    log_info "Enter $0"
    set_static_ip
}

main $*
