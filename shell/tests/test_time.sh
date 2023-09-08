#!/bin/bash

# 倒计时
function test_countdown() {
    echo "$FUNCNAME:-----------------------------"

    local time_s=3
    local i=

    for i in $(seq $time_s -1 1); do
        echo -n "countdown: ${i}s"
        sleep 1
        if [ $i -eq 1 ]; then
            break
        fi
        echo -e "\r\c"
    done
    echo ""

    echo "finish countdown"
}

# eg: countdown_and_stop 5
function countdown_and_stop() {
    local time_s=$1
    local i=
    local input=

    for i in $(seq $time_s -1 1); do
        echo -n "                                                              "
        echo -e "\r\c"
        echo -n "countdown: ${i}s"
        read -N 1 -t 1 -r -s input
        if [ -n "$input" ]; then
            break # or: return
        fi
        input=
        if [ $i -eq 1 ]; then
            break
        fi
        echo -e "\r\c"
    done
    echo ""
}

# 倒计时时若有用户输入则停止
function test_countdown_and_stop() {
    echo "$FUNCNAME:-----------------------------"

    countdown_and_stop 10

    echo "finish countdown"
}

function main() {
    test_countdown
    test_countdown_and_stop
}

main $*
