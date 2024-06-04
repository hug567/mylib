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

function limit_log_file_size() {
    local file=${LOGFILE}
    local line_num=
    local i=
    local delete_num=

    line_num=$(wc -l ${file} | awk '{print$1}')
    if [ "${line_num}" == "" ]; then
        return
    fi
    if [ ${line_num} -gt 1000 ]; then
        delete_num=$(expr ${line_num} - 1000)
        for i in $(seq 1 ${delete_num}); do
            sed -i '1d' ${file}
        done
    fi
}

function add_default_route() {
    local ip="10.110.0.3"
    local ret=

    ret=$(ip route show | grep "10.110.0.3" | awk '{print$3}')
    if [ "${ret}" == "" ]; then
        log_info "will add default route to: ${ip}"
        ip route add default via ${ip}
    fi
}

function set_dns_ip() {
    local dns_file="/etc/resolv.conf"
    local dns_ip="119.29.29.29"
    local ret=

    ret=$(cat ${dns_file} | grep "${dns_ip}")
    if [ "${ret}" == "" ]; then
        log_info "will add dns nameserver ${dns_ip} to ${dns_file}"
        echo "nameserver ${dns_ip}" >> ${dns_file}
    fi
}

function stop_net_card() {
    local name="enxaca0004390dc"
    local ret=

    ret=$(ip a show dev ${name} | head -n 1 | grep UP)
    if [ "${ret}" != "" ]; then
        log_info "will stop net card ${name}"
        ip link set ${name} down
    fi
}

function main() {
    export PATH="$PATH:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
    log_info "Enter $0"
    stop_net_card
    add_default_route
    set_dns_ip
    limit_log_file_size
}

main $*
