#!/bin/bash
# shell脚本中调用expect，在远端机器上执行命令
# 2024-04-07

function run_cmd_in_remote() {
    local cmd="${@}"
    local user="root"
    local ip="192.168.0.2"
    local password="root"
    local port="22"

    PS1="[host] $ "
    echo $PS1
expect <<EOF
    set timeout 10
    spawn ssh -p$port $user@$ip "$cmd"
    expect {
        "root*password" { send "$password\r" }
        "Are you sure you want to continue connecting" { send "yes\r"; exp_continue }
        timeout { exit 127 }
    }
    expect {
        "*\[host\]* $ " {}
        timeout { exit 127 }
    }
EOF
}

main() {
    run_cmd_in_remote "ls -l /"
    run_cmd_in_remote "cp -r /usr/bin/iq200 /home/root; sync"
    run_cmd_in_remote "ls -l /home/root"
}

main
