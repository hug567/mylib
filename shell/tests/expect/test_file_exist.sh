#!/bin/bash
# shell脚本中调用expect，判断远端文件是否存在
# 2024-04-07

function run_cmd_in_remote() {
    local cmd="${@}"
    local user="root"
    local ip="192.168.0.2"
    local password="root"
    local port="22"

    PS1="[host] $ "
    echo $PS1
    echo "[hx-debug] cmd: [$cmd]"
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

function remote_file_existed() {
    local file="$1"
    local cmd="if \\[ -f $file \\]; then echo is existed; else echo not existed; fi"
    local result=$(run_cmd_in_remote "$cmd" | grep "^is existed")

    if [ "$result" != "" ]; then
        return 0
    else
        return 1
    fi
}

function remote_file_md5() {
    local file=$1
    local cmd="md5sum $file"
    local result=$(run_cmd_in_remote "$cmd" | grep "$file" | grep -v md5sum | awk '{print$1}')

    echo "$result"
}

function file_need_update() {
    local local_file=$1
    local local_md5=
    local remote_file=$2
    local remote_md5=

    if [ ! -f $local_file ]; then
        return 1
    fi
    if ! remote_file_existed $remote_file; then
        return 0
    fi
}

main() {
    file_is_existed "/usr/bin/iq200/usr/bin/sendmsg"
    file_is_existed "/usr/bin/xxxxx"

    remote_file_md5 "/usr/bin/iq200/usr/bin/sendmsg"
}

main
