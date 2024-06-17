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
    echo "Usage: $0 <home>       copy configures to home dir"
}

function is_git_bash() {
    if [ -f /git-bash.exe ]; then
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

    copy_need_overwritten_files $dst
    copy_not_exist_files $dst
}

function main() {
    if [ $# != 1 ]; then
        usage
        exit 1
    fi
    local dst=$(cd $1; pwd)
    if [ ! -d $dst ]; then
        echo "$dst does not exist"
        exit 1
    fi
    copy_configures $dst
}

main $*
