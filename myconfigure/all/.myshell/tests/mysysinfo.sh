#!/bin/bash

cur_dir=$(cd $(dirname $BASH_SOURCE[0]); pwd)
source $cur_dir/../lib.sh

# kernel
# distro
# software version
#     vim
#     git
#     zsh
#     tmux

function kernel_info() {
    local info_file=$1

    if is_linux; then
        echo "current kernel is linux" >> $info_file
    fi
}

function distro_info() {
    local info_file=$1

    if is_ubuntu; then
        echo "current distro is ubutnu" >> $info_file
    fi
}

function shell_type() {
    local info_file=$1
}

function vim_version() {
    local info_file=$1
}

function git_version() {
    local info_file=$1
}

function zsh_version() {
    local info_file=$1
}

function tmux_version() {
    local info_file=$1
}

function main() {
    local info_file="/tmp/mysysinfo.txt"

    echo "[$(date +'%Y-%m-%d %H:%M:%S')] mysysinfo: ----------" > $info_file
    kernel_info $info_file
    distro_info $info_file
    shell_type $info_file
    vim_version $info_file
    git_version $info_file
    zsh_version $info_file
    tmux_version $info_file
}

main $*
