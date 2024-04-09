#!/bin/bash
# shell脚本中调用expect，scp文件到远端
# 2024-04-07

function scp_to_remote() {
    local files="$1"
    local dst_dir="$2"
    local user="root"
    local ip="192.168.0.2"
    local password="root"
    local port="22"

    PS1="[host] $ "
    echo $PS1
expect <<EOF
    set timeout 10
    spawn scp -P $port -r $files $user@$ip:$dst_dir
    expect {
        "Are you sure you want to continue connecting (yes/no)?" { send "yes\r"; exp_continue }
        "root*password:" { send "$password\r"; exp_continue }
        "Connect failed" { puts "ssh connect failed"; exit 126 }
        "100%" {}
        timeout { puts "ssh timeout"; exit 127 }
    }
    expect {
        "*\[host\]* $ " {}
        timeout { exit 127 }
    }
EOF
}

main() {
    scp_to_remote $HOME/docker.sh /home/root
}

main
