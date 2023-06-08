#!/usr/bin/bash

function is_linux() {
    local kernel=$(uname -s)
    if [ "$kernel" == "Linux" ]; then
        return 0 # true
    fi
    return 1 # false
}

function is_ubuntu() {
    if ! is_linux; then
        return 1
    fi
    local dis=$(cat /etc/os-release | grep "Ubuntu")
    if [ -n "$dis" ]; then
        return 0
    fi
    return 1
}

function __ubuntu_version() {
    local ver=$1
    if ! is_ubuntu; then
        return 1
    fi
    local version=$(cat /etc/os-release | grep "$ver")
    if [ -n "$version" ]; then
        return 0
    fi
    return 1
}

function is_ubuntu_18_04() {
    __ubuntu_version "18.04"
    return $?
}

function is_ubuntu_20_04() {
    __ubuntu_version "20.04"
    return $?
}

function is_ubuntu_22_04() {
    __ubuntu_version "22.04"
    return $?
}

function is_mobaxterm() {
    return 1
}

function is_gitbash() {
    return 1
}

function __cur_shell() {
    local shell=$1
    if [[ "$SHELL" =~ "$shell" ]]; then
        return 0
    else
        return 1
    fi
}

function is_bash() {
    __cur_shell "bash"
    return $?
}

function is_linux_bash() {
    if is_linux -a is_bash; then
        return 0
    else
       return 1
    fi
}

function is_zsh() {
    __cur_shell "zsh"
    return $?
}

function is_ash() {
    __cur_shell "/ash"
    return $?
}

function is_windows_nt() {
    local kernel=$(uname -s)
    if [[ "$kernel" =~ "$NT" ]]; then
        return 0
    else
        return 1
    fi
}

function is_gitbash() {
    if ! is_windows_nt; then
        return 1
    fi
    local dis=$(uname -s | grep "MINGW")
    if [ -z "$dis" ]; then
        return 1
    fi
    local os=$(uname -o | grep "Msys")
    if [ -z "$os" ]; then
        return 1
    fi
    return 0
}

function is_opensuse() {
    if ! is_linux; then
        return 1
    fi
    local dis=$(cat /etc/os-release | grep "openSUSE")
    if [ -n "$dis" ]; then
        return 0
    fi
    return 1
}

function __opensuse_version() {
    local ver=$1
    if ! is_opensuse; then
        return 1
    fi
    local version=$(cat /etc/os-release | grep "$ver")
    if [ -n "$version" ]; then
        return 0
    fi
    return 1
}

function is_opensuse_15_3() {
    __opensuse_version "15.3"
    return $?
}

function is_fedora() {
    if ! is_linux; then
        return 1
    fi
    local dis=$(cat /etc/os-release | grep "Fedora")
    if [ -n "$dis" ]; then
        return 0
    fi
    return 1
}

function __fedora_version() {
    local ver=$1
    if ! is_fedora; then
        return 1
    fi
    local version=$(cat /etc/os-release | grep "Fedora" | grep "$ver")
    if [ -n "$version" ]; then
        return 0
    fi
    return 1
}

function is_fedora_35() {
    __fedora_version "35"
    return $?
}
