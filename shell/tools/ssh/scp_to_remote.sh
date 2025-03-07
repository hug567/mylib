#!/usr/bin/bash

function usage() {
    echo "Usage: $0 ...                  ssh remote machine"
    echo "       -u user                 remote username"
    echo "       -i ip                   remote ip"
    echo "       -p port                 remote ssh port"
    echo "       -w passrord             remote user password"
    echo "       -o                      if no password"
    echo "       -h                      show help"
}

function is_linux() {
    local ret

    ret=$(uname -o | grep -E "Linux|linux|LINUX")
    if [ "${ret}" != "" ]; then
        return 0
    fi
    return 1
}

function init_ssh_connect() {
    local user=$1
    local ip=$2
    local port=$3
    local password=$4
    local no_password=$5

    if is_linux; then
        ping $ip -c 1 &> /dev/null
    else
        ping $ip -n 1 &> /dev/null
    fi
    if [ $? -ne 0 ]; then
        echo "ping $ip failed"
        exit 3
    fi
    sshpass -p $password ssh -p$port $user@$ip "ls" &> /dev/null
    if [ $? -eq 0 ]; then
        return 0
    fi
    ssh-keygen -f "${HOME}/.ssh/known_hosts" -R $ip
}

function ssh_remote() {
    local user=$1
    local ip=$2
    local port=$3
    local password=$4
    local no_password=$5

    if [ "${no_password}" != "true" ]; then
expect <<EOF
        set timeout 1000
        spawn ssh -p ${port} ${user}@${ip}
        expect {
            "${user}@*password" { send "${password}\r" }
            "Are you sure you want to continue connecting" { send "yes\r"; exp_continue }
            timeout { exit 127 }
        }
EOF
        echo ""
    fi
    sshpass -p ${password} ssh -p ${port} ${user}@${ip}
}

function main() {
    local user="root"
    local ip="192.168.0.2"
    local port="22"
    local password="root"
    local no_password="false"
    local file_or_dir
    local dst_dir="~"

    while [ -n "$1" ]; do
        case $1 in
            -u) user=$2; shift;;
            -i) ip=$2; shift;;
            -p) port=$2; shift;;
            -w) password=$2; shift;;
            -n) no_password="true";;
            -f) file_or_dir=$2; shift;;
            -d) dst_dir=$2; shift;;
            -h) usage; exit 1;
        esac
        shift
    done

    if [ "${file_or_dir}" == "" -o ! -e ${file_or_dir} ]; then
        echo "there is no file or dir: ${file_or_dir}"
        exit 1
    fi

    init_ssh_connect ${user} ${ip} ${port} ${password} ${no_password}
    #ssh_remote ${user} ${ip} ${port} ${password} ${no_password}
}

main $*
