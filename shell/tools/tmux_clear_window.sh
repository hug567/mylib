#!/bin/bash

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/lib/common.sh

function usage() {
    log_info "Usage: $0 <session> <window>"
}

function session_exist() {
    local session=$1
    local ret=$(tmux list-sessions | grep "^${session}: ")

    if [ -n "$ret" ]; then
        return 0
    else
        return 1
    fi
}

function window_exist() {
    local session=$1
    local window=$2
    local ret=$(tmux list-windows -t $session | grep "^${window}: ")

    if [ -n "$ret" ]; then
        return 0
    else
        return 1
    fi
}

function tmux_clear_window() {
    local session=$1
    local window=$2
    local panes=$(tmux list-panes -t $session:$window | awk -F ':' '{print$1}')

    echo "$panes" | while read pane
    do
        log_info "clear pane: $session:$window.$pane"
        tmux send -t $session:$window.$pane 'clear' C-m
    done
}

function main() {
    if [ $# != 2 ]; then
        usage
        exit 1
    fi
    local session=$1
    local window=$2
    if ! session_exist $session || ! window_exist $session $window; then
        log_error "session or window does not exist"
        usage
        exit 2
    fi
    tmux_clear_window $session $window
}

main $*
