# 判断当前shell
# 执行方式：bash test_cur_shell.sh
#           zsh test_cur_shell.sh
#           sh test_cur_shell.sh

is_bash() {
    if [ "${BASH_VERSION}" != "" ]; then
        return 0
    fi
    return 1
}

is_zsh() {
    if [ "${ZSH_VERSION}" != "" ]; then
        return 0
    fi
    return 1
}

test_cur_shell() {
    if is_bash; then
        echo "current is bash"
    fi
    if is_zsh; then
        echo "current is zsh"
    fi
}

main() {
    test_cur_shell
}

main
