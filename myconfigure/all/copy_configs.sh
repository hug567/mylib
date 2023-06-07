#!/bin/bash

SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
source $SCRIPT_DIR/.myshell/lib.sh

# needs to be overwritten unconditionally
OVERWRITTEN_FILES=(
    .myshell
    .mybash
    .myzsh
    .zshrc
    .oh-my-zsh
    .tmux.conf
    .tmux
    .gitconfig
    .tigrc
    copy_configs.sh
)

# if not exist in dst dir
NOT_EXIST_FILES=(
    .profile
)

# only gitbash needed config files
GITBASH_FILES=(
    .minttyrc
)

function usage() {
    echo "Usage: $0 <home>       copy configures to home dir"
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

    for f in ${NOT_EXIST_FILES[@]}; do
        fname=$(basename $f)
        if [ ! -e $dst/$fname ]; then
            copy_files $SCRIPT_DIR/$f $dst
        fi
    done
}

function copy_need_overwritten_files() {
    local dst=$1

    for f in ${OVERWRITTEN_FILES[@]}; do
        rm -rf $dst/$f
        copy_files $SCRIPT_DIR/$f $dst
    done
}

function copy_gitbash_files() {
    local dst=$1

    for f in ${GITBASH_FILES[@]}; do
        rm -rf $dst/$f
        copy_files $SCRIPT_DIR/$f $dst
    done
}

function copy_configures() {
    local dst=$1

    copy_need_overwritten_files $dst
    copy_not_exist_files $dst
    if is_gitbash; then
        copy_gitbash_files $dst
    fi
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
