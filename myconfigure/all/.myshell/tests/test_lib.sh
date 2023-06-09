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

    if is_in_docker; then
        echo "current is in docker"
    else
        echo "current is not in docker"
    fi
}

function test_linux_distro() {
    echo "$FUNCNAME:-----------------------------"
    if is_ubuntu; then
        echo "current os is ubuntu"
    elif is_opensuse; then
        echo "current os is opensuse"
    elif is_fedora; then
        echo "current os is fedora"
    else
        echo "current os is unknown distro"
    fi

    if is_ubuntu_18_04; then
        echo "current os is ubuntu 18.04"
    elif is_ubuntu_20_04; then
        echo "current os is ubuntu 20.04"
    elif is_ubuntu_22_04; then
        echo "current os is ubuntu 22.04"
    elif is_opensuse_15_3; then
        echo "current os is opensuse 15.3"
    elif is_fedora_35; then
        echo "current os is fedora 35"
    else
        echo "current os is unknown distro"
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
    elif is_mobaxterm; then
        echo "current is mobaxterm"
    else
        echo "current is not gitbash"
    fi
}

function main() {
    test_kernel
    test_linux_distro
    test_shell
    test_gitbash
}

main $*
