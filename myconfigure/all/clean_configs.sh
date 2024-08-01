#!/bin/bash

ALL_FILES=(
    .myshell
    .zshrc
    .oh-my-zsh
    .tmux.conf
    .tmux
    .gitconfig
    .tigrc
    .vimrc
    .vim
    .profile
    .minttyrc
    copy_configs.sh
    clean_configs.sh
)

function usage() {
    echo "Usage: $0 <dir>      clean configures in dir"
    echo "   eg: $0 ./"
}

function clean_configures() {
    local dst=${1}
    local file=

    cd ${dst}

    for file in ${ALL_FILES[@]}; do
        if [ -e ${file} ]; then
            echo "will delete ${file}"
            rm -rf ${file}
        fi
    done
}

function main() {
    local dst=
    local abs_dst=

    if [ "$1" == "-h" -o $# != 1 ]; then
        usage
        exit 1
    fi
    local dst="${1}"
    if [ "${dst}" == "" -o  ! -d "${dst}" ]; then
        echo "dir [${dst}] does not exist"
        exit 1
    fi
    local abs_dst=$(cd ${dst}; pwd)
    clean_configures ${abs_dst}
}

main $*
