#!/bin/bash

function task_is_finished() {
    task=$1
    ret=$(ps | grep $task | grep -v "grep")
    if [ "$ret" = "" ]; then
        return 0 # true
    else
        return 1 # false
    fi
}

function wait_task_finish() {
    task=$1
    while true; do
        if task_is_finished $task; then
            return
        else
            sleep 1
        fi
    done
}

################################################################################
function test01() {
    if task_is_finished htop; then
        echo "htop is finished"
    else
        echo "htop is running"
    fi
}

if task_is_finished zsh; then
    echo "zsh is finished"
else
    echo "zsh is running"
fi

task="sleep"
if task_is_finished $task; then
    echo "$task is finished"
else
    echo "$task is running"
fi

sleep 10 &
wait_task_finish sleep
echo "sleep is finished"

function test04() {
    echo "test04:"
    task="zsh"
    if ! task_is_finished $task; then
        echo "$task is running"
    fi
}

function main() {
    test01
    test04
}

main
