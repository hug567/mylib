#!/usr/bin/zsh

function __return_true() {
    return 0
}

function __return_false() {
    return 1
}

function test_true_false() {
    echo "[test_true_false]:-------------------------------"

    if __return_true; then
        echo "return true"
    fi
    if ! __return_false; then
        echo "return false"
    fi
}

function main() {
    test_true_false
}

main
