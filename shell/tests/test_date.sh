#!/bin/bash

# eg:
#   START_TIME=$(date +%s)
#   END_TIME=$(date +%s)
#   time_diff $END_TIME $START_TIME
function time_diff()
{
    local end_time=$1
    local start_time=$2
    local diff_s=$(( $end_time - $start_time ))
    local hour=$(( $diff_s / 3600 ))
    local min=$(( ($diff_s - $hour * 3600) / 60 ))
    local second=$(( $diff_s - ($hour * 3600) - ($min * 60) ))
    printf "%02d:%02d:%02d" $hour $min $second
}

function test_time_diff() {
    echo "$FUNCNAME:-----------------------------"

    local START_TIME=$(date +%s)
    local END_TIME=$(date +%s)
    echo "time diff: $(time_diff 0 0)"
    echo "time diff: $(time_diff 100 0)"
    echo "time diff: $(time_diff 10000 0)"
    echo "time diff: $(time_diff 10000 123)"
    echo "time diff: $(time_diff $END_TIME $START_TIME)"
}

function main() {
    test_time_diff
}

main
