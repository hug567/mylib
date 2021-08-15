#!/bin/bash

# eg:
#   START_TIME=$(date +%s)
#   END_TIME=$(date +%s)
#   time_diff $END_TIME $START_TIME
time_diff()
{
    end_time=$1
    start_time=$2
    diff_s=$(( $end_time - $start_time ))
    hour=$(( $diff_s / 3600 ))
    min=$(( ($diff_s - $hour * 3600) / 60 ))
    second=$(( $diff_s - ($hour * 3600) - ($min * 60) ))
    printf "%02d:%02d:%02d" $hour $min $second
}

START_TIME=$(date +%s)
END_TIME=$(date +%s)

echo "time diff: $(time_diff 0 0)"
echo "time diff: $(time_diff 100 0)"
echo "time diff: $(time_diff 10000 0)"
echo "time diff: $(time_diff 10000 123)"
echo "time diff: $(time_diff $END_TIME $START_TIME)"
