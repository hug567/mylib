#!/bin/bash

# sleep睡眠小数秒，只有bash支持
function test_sleep_decimals() {
    echo "$FUNCNAME:-----------------------------------------------------------"

    echo "start date: $(date '+%Y-%m-%d %H:%M:%S')"
    for i in $(seq 0 9); do
        echo "[$(date '+%Y-%m-%d %H:%M:%S')] i: $i"
        sleep 0.1
    done
    echo "end date  : $(date '+%Y-%m-%d %H:%M:%S')"
}

function main() {
    test_sleep_decimals
    echo ""
}

main $*
