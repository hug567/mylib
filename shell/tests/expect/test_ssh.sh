#!/bin/bash

# call expect in shell script

#set -x

reset_known_hosts() {
    local user=$1
    local ip=$2
    local passwd=$3
    local port=$4

    ping $ip -c 1 > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "ping $ip failed"
        exit 1
    fi
    sshpass -p $passwd ssh -o StrictHostKeyChecking=no -p $port $user@${ip} "ls" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "will remove $ip:$port in known_hosts"
        ssh-keygen -f "/home/$(whoami)/.ssh/known_hosts" -R "[$ip]:$port" > /dev/null 2>&1
    fi
}

ssh_server() {
    local user=$1
    local ip=$2
    local passwd=$3
    local port=$4
    local cmd="${*:5}"

    reset_known_hosts $user $ip $passwd $port

    PS1="[host] $ "
    echo $PS1
expect <<EOF
    set timeout 10
    spawn ssh -o StrictHostKeyChecking=no -p$port $user@$ip
    expect {
        "*yes/no*" { send "yes\r"; exp_continue}
        "*password*" { send "$passwd\r" }
        timeout { exit 127 }
    }
    expect "*$user@*"
    send "$cmd\n"
    expect "*$user@*"
    send "exit\n"
    expect "*Connection*$ip*closed*"
    expect "*\[host\] $ *"
EOF
}

run_cmd_in_server() {
    ssh_server jenkins 10.116.36.33 jenkins 1000 "pwd; ls -l ~"
}

main() {
    run_cmd_in_server
}

main
