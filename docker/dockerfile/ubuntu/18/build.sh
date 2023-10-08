#!/bin/bash

MYLIB="$HOME/code/mylib"

function prepare_files() {
    local tmpdir=$1

    cp $MYLIB/docker/dockerfile/ubuntu/18/base.df $tmpdir
    cp $MYLIB/myconfigure/ubuntu/18.04/sources.list $tmpdir

    mkdir -p $tmpdir/homefiles
    local config_files=(
        .gitconfig
        .minttyrc
        .myshell
        .oh-my-zsh
        .profile
        .tigrc
        .tmux
        .tmux.conf
        .vim
        .vimrc
        .zshrc
    )
    for file in ${config_files[@]}; do
        cp -r $MYLIB/myconfigure/all/$file $tmpdir/homefiles
    done
}

function build_image() {
    local tmpdir=$1

    cd $tmpdir
    docker build -t myubuntu18:v0.1 -f base.df ./
}

function main() {
    local tmpdir="/tmp/dockerfile/ubuntu/18"

    if [ -d $tmpdir ]; then
        rm -rf $tmpdir
    fi
    mkdir -p $tmpdir

    prepare_files $tmpdir
    build_image $tmpdir
}

main $*
