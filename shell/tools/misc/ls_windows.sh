#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../..; pwd)
source ${MYLIB}/shell/lib/common.sh

function usage() {
    log_info "$0 <dir>   list files in remote windows"
}

function list_files() {
    local dir=${1} # unix风格路径：/e/fpga_project/vivado_2016.2/RUV_300B/
    local user="huangxing"
    local ip=10.110.0.4
    local passwd="RhoHx2023,01"
    local dir_tail=${dir[@]:2} # 相对盘符的路径：/fpga_project/vivado_2016.2/RUV_300B/
    local dir_disk="${dir[@]:1:1}:" # windows风格盘符：e:
    local dir_cmd="${dir}${dir_tail}" # windows风格全路径：e:/fpga_project/vivado_2016.2/RUV_300B/

    PS1="[host] $ "
expect <<EOF
    set timeout 1000
    spawn ssh ${user}@${ip}
    expect {
        "${user}@${ip}'s password" { send "${passwd}\r"; exp_continue}
        "huangxing@DESKTOP-8606LAV" {}
        timeout { exit 127 }
    }

    send "D: && cd \"\\\Program Files\\\Git\\\bin\" && bash\r"
    expect {
        "MINGW64" {exp_continue}
        "$ " {}
        timeout { exit 127 }
    }

    send "ls ${dir}\r"
    expect {
        "MINGW64" {exp_continue}
        "$ " {}
        timeout { exit 127 }
    }

    send "exit\r"
    expect {
        "huangxing@DESKTOP-8606LAV" {exp_continue}
        ">" {}
        timeout { exit 127 }
    }

    send "exit\r"
    expect {
        "closed" {exp_continue}
        "*\[host\]" {exp_continue}
        "$ " {}
        timeout { exit 127 }
    }
EOF
}

function main() {
    local dir=${1}

    if [ $# -ne 1 ]; then
        usage
        exit 1
    fi

    list_files ${dir}
}

main $*
