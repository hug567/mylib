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

function __cur_shell() {
    local shell=$1
    local cmd=
    local PATH_OLD=
    local ret=

    PATH_OLD=$PATH
    PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
    cmd=$(ls -l /proc/$$/exe | grep "$shell")
    if [ -n "$cmd" ]; then
        ret=0
    else
        ret=1
    fi
    PATH=$PATH_OLD
    return $ret
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
    if [[ "$kernel" =~ "NT" ]]; then
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

function is_mobaxterm() {
    if ! is_windows_nt; then
        return 1
    fi
    # uame -s: CYGWIN_NT-10.0-WOW
    if [ ! -f /usr/share/mobaxterm ]; then
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

function is_in_docker() {
    if ! is_linux; then
        return 1
    fi
    if [ -f /.dockerenv ]; then
        return 0
    else
        return 1
    fi
}

function path_existed_bash() {
    local path=$1
    local pathes=(${PATH//:/ })

    for p in ${pathes[@]}; do
        if [ "$p" = "$path" ]; then
            return 0
        fi
    done
    return 1
}

function path_existed_zsh() {
    local path=$1
    local pathes=("${(@s/:/)PATH}")

    for p in ${pathes[@]}; do
        if [ "$p" = "$path" ]; then
            return 0
        fi
    done
    return 1
}

function path_existed() {
    if is_bash; then
        path_existed_bash $1
        return $?
    elif is_zsh; then
        path_existed_zsh $1
        return $?
    else
        echo "It is currently neither bash nor zsh"
    fi
}

function add_path() {
    local path=$1
    if [ ! -d "$path" ]; then
        return
    fi
    local abs_path=$(cd $path; pwd)
    if path_existed "$abs_path"; then
        return
    fi
    export PATH="$path:$PATH"
}

function source_file() {
    local file=$1
    if [ -f $file -o -L $file ]; then
        source $file
    fi
}
