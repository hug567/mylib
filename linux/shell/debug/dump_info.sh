#!/bin/bash

function dump_all_task_stack() {
    log_file=$1
    rm $log_file
    pids=$(ls -1 /proc)
    echo "$pids" | while read pid
    do
        stack_file="/proc/$pid/stack"
        if [ -f $stack_file ]; then
            echo "task: $(cat /proc/$pid/comm), pid: $pid, stack:" >> $log_file
            cat $stack_file >> $log_file
            echo "" >> $log_file
        fi
    done
}

function main() {
    dump_all_task_stack ./all_task_stack.log
}

main
