#!/usr/bin/bash

function usage() {
    echo "Usage: $0 <user> <ip> <port> <password>          ssh remote machine"
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

    if is_linux; then
        echo "[hx-debug] current is linux"
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

expect <<EOF
    set timeout 1000
    spawn ssh -p ${port} ${user}@${ip}
    expect {
        "${user}@*password" { send "${password}\r"}
        "Are you sure you want to continue connecting" { send "yes\r"; exp_continue}
        timeout { exit 127 }
    }
EOF
    echo ""
    sshpass -p ${password} ssh -p ${port} ${user}@${ip}
}

function main() {
    local user=$1
    local ip=$2
    local port=$3
    local password=$4

    if [ $# -ne 4 ]; then
        usage
        exit
    fi

    init_ssh_connect ${user} ${ip} ${port} ${password}
    ssh_remote ${user} ${ip} ${port} ${password}
}

main $*
