#!/bin/bash

cur_dir=$(cd $(dirname $BASH_SOURCE[0]); pwd)
source $cur_dir/../lib.sh

function test_kernel() {
    echo "$FUNCNAME:-----------------------------"
    if is_linux; then
        echo "current os is linux"
    else
        echo "current os is not linux"
    fi
}

function test_ubuntu() {
    echo "$FUNCNAME:-----------------------------"
    if is_ubuntu; then
        echo "current os is ubuntu"
    else
        echo "current os is not ubuntu"
    fi

    if is_ubuntu_18_04; then
        echo "current os is ubuntu 18.04"
    elif is_ubuntu_20_04; then
        echo "current os is ubuntu 20.04"
    elif is_ubuntu_22_04; then
        echo "current os is ubuntu 22.04"
    else
        echo "current os is unknown ubuntu version"
    fi
}

function test_shell() {
    echo "$FUNCNAME:-----------------------------"
    if is_bash; then
        echo "current shell is bash"
    elif is_zsh; then
        echo "current shell is zsh"
    elif is_ash; then
        echo "current shell is ash"
    else
        echo "Cannot recognize the current shell"
    fi

    if is_linux_bash; then
        echo "current is linux bash"
    fi
}

function test_gitbash() {
    echo "$FUNCNAME:-----------------------------"

    if is_gitbash; then
        echo "current is gitbash"
    else
        echo "current is not gitbash"
    fi
}

function main() {
    test_kernel
    test_ubuntu
    test_shell
    test_gitbash
}

main $*
