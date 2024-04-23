prepare() {
    local cur_dir=

    if [ "${BASH_VERSION}" != "" ]; then
        cur_dir=$(cd $(dirname $BASH_SOURCE[0]); pwd)
    elif [ "${ZSH_VERSION}" != "" ]; then
        cur_dir=$(cd $(dirname ${PWD}/${ZSH_ARGZERO}); pwd)
    else
        echo "current is not bash or zsh"
        exit 1
    fi
    echo "cur_dir: $cur_dir"
    source $cur_dir/../lib.sh
}

test_kernel() {
    echo "test_kernel:---------------------------------------------------------"
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

test_linux_distro() {
    echo "test_linux_distro:---------------------------------------------------"
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

test_shell() {
    echo "test_shell:----------------------------------------------------------"
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

test_gitbash() {
    echo "test_gitbash:--------------------------------------------------------"

    if is_gitbash; then
        echo "current is gitbash"
    elif is_mobaxterm; then
        echo "current is mobaxterm"
    else
        echo "current is not gitbash"
    fi
}

test_add_path() {
    echo "test_add_path:-------------------------------------------------------"
    add_path "/usr/bin"
    echo "${PATH}"
}

main() {
    prepare
    test_kernel
    test_linux_distro
    test_shell
    test_gitbash
    test_add_path
}

main $*
