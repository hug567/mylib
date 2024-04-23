is_linux() {
    local kernel=$(uname -s)
    if [ "$kernel" = "Linux" ]; then
        return 0 # true
    fi
    return 1 # false
}

is_ubuntu() {
    if ! is_linux; then
        return 1
    fi
    local dis=$(cat /etc/os-release | grep "Ubuntu")
    if [ -n "${dis}" ]; then
        return 0
    fi
    return 1
}

__ubuntu_version() {
    local ver=$1
    if ! is_ubuntu; then
        return 1
    fi
    local version=$(cat /etc/os-release | grep "$ver")
    if [ -n "${version}" ]; then
        return 0
    fi
    return 1
}

is_ubuntu_18_04() {
    __ubuntu_version "18.04"
    return $?
}

is_ubuntu_20_04() {
    __ubuntu_version "20.04"
    return $?
}

is_ubuntu_22_04() {
    __ubuntu_version "22.04"
    return $?
}

__cur_shell() {
    local shell=$1
    local cmd=""
    local PATH_OLD=""
    local ret=""

    PATH_OLD=$PATH
    PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
    cmd=$(ls -l /proc/$$/exe | grep "$shell")
    if [ "$cmd" != "" ]; then
        ret=0
    else
        ret=1
    fi
    PATH=$PATH_OLD
    return $ret
}

is_bash() {
    if [ "${BASH_VERSION}" != "" ]; then
        return 0
    fi
    return 1
}

is_linux_bash() {
    if ! is_linux; then
        return 1
    fi
    if ! is_bash; then
        return 1
    fi
    return 0
}

is_zsh() {
    if [ "${ZSH_VERSION}" != "" ]; then
        return 0
    fi
    return 1
}

is_ash() {
    __cur_shell "/ash"
    return $?
}

is_windows_nt() {
    local kernel=$(uname -s)
    if [[ "$kernel" =~ "NT" ]]; then
        return 0
    else
        return 1
    fi
}

is_gitbash() {
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

is_mobaxterm() {
    if ! is_windows_nt; then
        return 1
    fi
    # uame -s: CYGWIN_NT-10.0-WOW
    if [ ! -f /usr/share/mobaxterm ]; then
        return 1
    fi
    return 0
}

is_opensuse() {
    if ! is_linux; then
        return 1
    fi
    local dis=$(cat /etc/os-release | grep "openSUSE")
    if [ -n "$dis" ]; then
        return 0
    fi
    return 1
}

__opensuse_version() {
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

is_opensuse_15_3() {
    __opensuse_version "15.3"
    return $?
}

is_fedora() {
    if ! is_linux; then
        return 1
    fi
    local dis=$(cat /etc/os-release | grep "Fedora")
    if [ -n "$dis" ]; then
        return 0
    fi
    return 1
}

__fedora_version() {
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

is_fedora_35() {
    __fedora_version "35"
    return $?
}

is_in_docker() {
    if ! is_linux; then
        return 1
    fi
    if [ -f /.dockerenv ]; then
        return 0
    else
        return 1
    fi
}

path_existed() {
    local tmp_path=$1
    local pathes=""
    local p=""

    if is_bash; then
        pathes=(${PATH//:/ })
    elif is_zsh; then
        pathes=("${(@s/:/)PATH}")
    fi
    for p in ${pathes[@]}; do
        if [ "$p" = "$tmp_path" ]; then
            return 0
        fi
    done
    return 1
}

add_path() {
    local tmp_path=$1
    if [ ! -d "$tmp_path" ]; then
        return
    fi
    local abs_path=$(cd $tmp_path; pwd)
    if path_existed "$abs_path"; then
        return
    fi
    export PATH="$tmp_path:$PATH"
}

source_file() {
    local file=$1
    if [ -f $file -o -L $file ]; then
        source $file
    fi
}
