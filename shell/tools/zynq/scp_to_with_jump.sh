#!/bin/bash
# 通过跳板机发送文件到内部机器，使用expect自动输入密码，需先配置~/.ssh/config
# 2024-08-16

function usage() {
    echo "Usage: $0 <dst_dir> <file/dir>...    scp file/dir to antenna with ssh jump"
}

function scp_to_antenna() {
    local file_or_dir=${1}
    local dst_dir=${2}
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
    spawn scp -r ${file_or_dir} antenna:${dst_dir}
    expect {
        "${jump_name}@*password" { send "${jump_passwd}\r"; exp_continue }
        "${antenna_name}@${antenna_ip}'s password" { send "${antenna_passwd}\r"; exp_continue }
        "Are you sure you want to continue connecting" { send "yes\r"; exp_continue}
        "100%" {}
        timeout { exit 127 }
    }
EOF
}

function main() {
    local dst_dir=$1
    local files="${@:2}"
    local src_file=
    local i=o

    if [ $# -lt 2 -o "$1" == "-h" ]; then
        usage
        exit
    fi

    ssh-keygen -R 192.168.0.2
    for src_file in $(echo "$files"); do
        let i=i+1
        echo "[$i]: -----------------------------------------------------------"
        if [ ! -e $src_file ]; then
             echo "[${PWD}]: file or dir [$src_file] does not exist"
             continue
        fi
        scp_to_antenna $src_file $dst_dir
    done
}

main $*
