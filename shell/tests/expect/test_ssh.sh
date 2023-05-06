#!/bin/bash

# call expect in shell script

ssh_server() {
    local user=$1
    local ip=$2
    local passwd=$3
    local port=$4
    local cmd="${*:5}"

    PS1="[host] $ "
    echo $PS1
expect <<EOF
    set timeout 10
    spawn ssh -p$port $user@$ip
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
    ssh_server jenkins 10.116.36.44 jenkins 1000 "pwd; ls -l ~"
}

main() {
    run_cmd_in_server
}

main