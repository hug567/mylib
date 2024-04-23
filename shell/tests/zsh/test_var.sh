#!/usr/bin/zsh

function test_zsh_env_val() {
    echo "[test_zsh_env_val]:--------------------------------------------------"

    echo "ZSH_SUBSHELL = ${ZSH_SUBSHELL}"
    echo "ZSH_ARGZERO = ${ZSH_ARGZERO}"
    echo "ZSH_NAME = ${ZSH_NAME}"
    echo "ZSH_PATCHLEVEL = ${ZSH_PATCHLEVEL}"
    echo "ZSH_VERSION = ${ZSH_VERSION}"
}

function main() {
    test_zsh_env_val
}

main
