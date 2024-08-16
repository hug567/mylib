#!/bin/bash
# 通过跳板机发送文件到内部机器，使用expect自动输入密码，需先配置~/.ssh/config
# 2024-08-16

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
    local files="$*"
    local file=
    local i=0

    if [ $# -eq 0 -o "$1" == "-h" ]; then
        usage
        exit
    fi
    for file in ${files}; do
        if [ ! -e ${file} ]; then
            echo "there is no: ${file}"
            continue
        fi
        let i=i+1
        echo "- [${i}] --------------------------------------------------------"
        scp_to_antenna "${file}"
    done
}

main $*
