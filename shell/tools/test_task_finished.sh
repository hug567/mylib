#!/bin/bash

function task_is_finished() {
    local task="$1"
    local ret=$(ps | grep "$task" | grep -v " grep ")
    if [ "$ret" = "" ]; then
        return 0 # true
    else
        return 1 # false
    fi
}

function task_is_running() {
    local task="$1"
    local ret=$(ps | grep "$task" | grep -v " grep ")
    if [ "$ret" != "" ]; then
        return 0 # true
    else
        return 1 # false
    fi
}

function wait_task_finish() {
    local task="$1"
    while true; do
        if task_is_finished "$task"; then
            return
        else
            sleep 1
        fi
    done
}

# eg: kill_9_task "iperf.*-c"
function kill_9_task() {
    local task="$1"
    local tasks=$(ps aux | grep "$task" | grep -v " grep ")
    if [ "$tasks" = "" ]; then
        return
    fi
    echo "$tasks" | while read onetask
    do
        local pid=$(echo "$onetask" | awk -F ' ' '{print$2}')
        kill -9 $pid
        log_info "run cmd: kill -9 $pid"
        log_info "task: [$onetask]"
    done
}

################################################################################
function test01() {
    echo "test01:"
    if task_is_finished htop; then
        echo "htop is finished"
    else
        echo "htop is running"
    fi

    if task_is_finished zsh; then
        echo "zsh is finished"
    else
        echo "zsh is running"
    fi
}

function test02() {
    echo "test02:"
    local task="sleep"
    if task_is_finished $task; then
        echo "$task is finished"
    else
        echo "$task is running"
    fi
}

function test03() {
    echo "test03:"
    sleep 5 &
    wait_task_finish sleep
    echo "sleep is finished"
}

function test04() {
    echo "test04:"
    local task="zsh"
    if ! task_is_finished $task; then
        echo "$task is running"
    fi
    if task_is_running $task; then
        echo "$task is running"
    fi
}

function test05() {
    echo "test05:"
    local task1="zsh"
    local task2="htop"
    if task_is_finished $task1 || task_is_finished $task2; then
        echo "$task1 or $task2 is finished"
    fi
}

function test06() {
    echo "test06:"
    local task="sshd"
    local pids=$(ps aux | grep "$task" | grep -v " grep " | awk -F ' ' '{print$2}')
    echo "$pids" | while read pid
    do
        echo "$task pid: $pid"
    done
}

function main() {
    test01
    test02
    test03
    test04
    test05
    test06
}

main
