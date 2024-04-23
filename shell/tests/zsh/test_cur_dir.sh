#!/usr/bin/zsh
# 获取当前zsh脚本所在目录

function test_cur_dir() {
    echo "[test_cur_dir]:------------------------------------------------------"

    echo "cur dir = $(cd $(dirname ${PWD}/${ZSH_ARGZERO}); pwd)"
}

function main() {
    test_cur_dir
}

main
