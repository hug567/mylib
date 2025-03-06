#!/bin/bash

SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
source $SCRIPT_DIR/.myshell/lib.sh

# needs to be overwritten unconditionally
GIT_BASH_FILES=(
    .myshell
    .gitconfig
    .vimrc
    .vim
    .minttyrc
    copy_configs.sh
)

LINUX_FILES=(
    .myshell
    .zshrc
    .oh-my-zsh
    .tmux.conf
    .tmux
    .gitconfig
    .tigrc
    .vimrc
    .vim
    copy_configs.sh
)

# if not exist in dst dir
NOT_EXIST_FILES=(
    .profile
)

function usage() {
    echo "Usage: $0 <home> <environment>      copy configures to home dir"
    echo "   eg: $0 \$HOME linux"
    echo "   eg: $0 \$HOME gitbash"
    echo "   eg: $0 \$HOME mobaxterm"
    echo "   eg: $0 \$HOME cygwin"
}

function vim_version() {
    local version

    version=$(vim --version | grep "Vi IMproved" | head -n 1 | awk '{print$5}')
    echo -n "${version}"
}

function is_git_bash() {
    if [ -f /git-bash.exe ]; then
        return 0
    fi
    return 1
}

function is_cygwin() {
    local ret=$(uname -o)
    if [ "${ret}" == "Cygwin" ]; then
        return 0
    fi
    return 1
}

function copy_files() {
    local files=$1
    local dst=$2

    echo "copy [$files] to [$dst]"
    cp -r $files $dst
}

function copy_not_exist_files() {
    local dst=$1
    local fname=
    local f=

    for f in ${NOT_EXIST_FILES[@]}; do
        fname=$(basename $f)
        if [ ! -e $dst/$fname ]; then
            copy_files $SCRIPT_DIR/$f $dst
        fi
    done
}

function copy_need_overwritten_files() {
    local dst=$1
    local files="${LINUX_FILES[@]}"
    local f=

    if is_git_bash; then
        echo "current is git bash"
        files="${GIT_BASH_FILES[@]}"
    fi
    for f in ${files[@]}; do
        rm -rf $dst/$f
        copy_files $SCRIPT_DIR/$f $dst
    done
}

function copy_configures() {
    local dst=$1
    local environment=$2

    copy_need_overwritten_files $dst
    copy_not_exist_files $dst
}

function dos2unix_one_file() {
    local file=$1
    if [ ! -f "${file}" ]; then
        echo "there is no file: ${file}"
        return
    fi
    dos2unix ${file}
}

function dos2unix_all_files_in_dir() {
    local dir=${1}
    local all_files
    local file

    if [ ! -d "${dir}" ]; then
        echo "there is no dir: ${dir}"
        return
    fi
    all_files=$(find ${dir} -name "*")
    if [ "${all_files}" == "" ]; then
        echo "there is no file in dir: ${dir}"
        return
    fi
    echo "${all_files}" | while read file; do
        if [ ! -f "${file}" ]; then
            continue
        fi
        dos2unix_one_file ${file}
    done
}

function dos2unix_files() {
    local dst=$1
    local ret

    ret=$(which dos2unix)
    if [ "${ret}" == "" ]; then
        echo "there is no cmd: dos2unix"
        return
    fi
    dos2unix_one_file ${dst}/.tmux.conf
    dos2unix_all_files_in_dir ${dst}/.tmux/conf

    dos2unix_one_file ${dst}/.vimrc
    dos2unix_all_files_in_dir ${dst}/.vim/autoload
    dos2unix_all_files_in_dir ${dst}/.vim/colors
    dos2unix_all_files_in_dir ${dst}/.vim/plugin
    dos2unix_all_files_in_dir ${dst}/.vim/plugged
    dos2unix_all_files_in_dir ${dst}/.vim/scripts
    dos2unix_all_files_in_dir ${dst}/.vim/vimrc
}

function main() {
    local dst=
    local abs_dst=

    if [ "$1" == "-h" -o $# != 2 ]; then
        usage
        exit 1
    fi
    local dst="${1}"
    if [ "${dst}" == "" -o  ! -d "${dst}" ]; then
        echo "dir [${dst}] does not exist"
        exit 1
    fi
    local abs_dst=$(cd ${dst}; pwd)
    copy_configures ${abs_dst} ${environment}

    dos2unix_files ${abs_dst}
}

main $*
