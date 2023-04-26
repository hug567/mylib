#!/bin/bash

# call expect in shell script

ssh_server() {
    local user=$1
    local ip=$2
    local passwd=$3
    local port=$4

    PS1="[host] $ "
    echo $PS1
expect <<EOF
    set timeout 10
    spawn ssh -p$port $user@$ip
    expect "*password*"
    send "$passwd\n"
    expect "*jenkins@*"
    send "ls\n"
    expect "*jenkins@*"
    send "exit\n"
    expect "*Connection*$ip*closed*"
    expect "*\[host\] $ *"
EOF
}

scp_to_server() {
    local user=$1
    local ip=$2
    local passwd=$3
    local port=$4
    local file=$5

    PS1="[host] $ "
    echo $PS1
expect <<EOF
    set timeout 10000
    spawn scp -P$port -r $file $user@$ip:~
    expect "*password*"
    send "$passwd\n"
    expect "*100%*"
    set timeout 10
    expect "*\[host\] $ *"
    spawn ssh -p$port $user@$ip "ls"
    expect "*password*"
    send "$passwd\n"
    expect "*\[host\] $ *"
EOF
}

main() {
    ssh_server jenkins 10.116.36.44 jenkins 1000
    scp_to_server jenkins 10.116.36.44 jenkins 1000 /tmp/vim_tmp.txt
}

main
