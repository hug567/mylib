#!/bin/bash

function usage() {
    echo "Usage: $0 <file/dir>    scp file/dir to antenna with ssh jump"
}

function scp_to_antenna() {
    local file=${1}
    local jump_name=rhosoon
    local jump_ip=192.168.99.50
    local jump_passwd=R123456
    local antenna_name=root
    local antenna_ip=192.168.0.2
    local antenna_passwd=root

    # 在~/.ssh/config中配置到天线的代理
    # Host antenna
    #     User root
    #     Hostname 192.168.0.2
    #     ProxyCommand ssh rhosoon@192.168.99.50 -W %h:%p B

expect <<EOF
    set timeout 1000
    spawn scp ${file} antenna:~
    expect {
        "${jump_name}@${jump_ip}'s password" { send "${jump_passwd}\r"; exp_continue }
        "${antenna_name}@${antenna_ip}'s password" { send "${antenna_passwd}\r"; exp_continue }
        "Are you sure you want to continue connecting" { send "yes\r"; exp_continue}
        "100%" {}
        timeout { exit 127 }
    }
EOF
}

function main() {
    local file=${1}

    if [ $# -ne 1 ]; then
        usage
        exit
    fi
    if [ ! -e ${file} ]; then
        echo "there is no: ${file}"
    fi

    scp_to_antenna "${file}"
}

main $*
