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
    if is_windows_nt; then
        echo "current kernel is windowd nt" >> $info_file
    fi
}

function distro_info() {
    local info_file=$1

    if is_ubuntu; then
        echo "current distro is ubutnu" >> $info_file
    fi
    if is_ubuntu_18_04; then
        echo "current distro is ubutnu 18.04" >> $info_file
    fi
    if is_ubuntu_20_04; then
        echo "current distro is ubutnu 20.04" >> $info_file
    fi
    if is_ubuntu_22_04; then
        echo "current distro is ubutnu 22.04" >> $info_file
    fi
    if is_opensuse; then
        echo "current distro is opensuse" >> $info_file
    fi
    if is_opensuse_15_3; then
        echo "current distro is opensuse 15.3" >> $info_file
    fi
    if is_fedora; then
        echo "current distro is fedora" >> $info_file
    fi
    if is_fedora_35; then
        echo "current distro is fedora 35" >> $info_file
    fi
    if is_in_docker; then
        echo "current is in docker" >> $info_file
    fi
}

function shell_type() {
    local info_file=$1

    if is_bash; then
        echo "current shell is bash" >> $info_file
    fi
    if is_linux_bash; then
        echo "current shell is bash in linux" >> $info_file
    fi
    if is_zsh; then
        echo "current shell is zsh" >> $info_file
    fi
    if is_ash; then
        echo "current shell is ash" >> $info_file
    fi
    if is_gitbash; then
        echo "current is gitbash" >> $info_file
    fi
    if is_mobaxterm; then
        echo "current is mobaxterm" >> $info_file
    fi
}

function vim_version() {
    local info_file=$1

    vim --version | grep "^VIM" >> $info_file
}

function git_version() {
    local info_file=$1

    git --version >> $info_file
}

function zsh_version() {
    local info_file=$1

    zsh --version >> $info_file
}

function tmux_version() {
    local info_file=$1

    tmux -V >> $info_file
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

    ls -l /proc/$$/exe >> $info_file
}

main $*
