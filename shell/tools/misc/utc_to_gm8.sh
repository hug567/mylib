#!/bin/sh
# utc时间戳转北京时间
# Create: 2025-03-17 14:57:02

function utc_to_gm8() {
   local utc_time=$1
}

function main() {
    local utc_time="316570745"

    utc_to_gm8 ${utc_time}
}

main $*
