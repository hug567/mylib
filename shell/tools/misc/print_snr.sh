#!/bin/sh
# 多列打印snr
# 2024-04-27

LINE_OLD=""
DEFAULT_COL_SIZE=130

function usage() {
    echo "Usage: $0 [col_size]        print snr, col size can be specified"
    echo "   eg: $0"
    echo "   eg: $0 100"
}

function print_to_tail() {
    local new="$1"
    local col_size=$2
    local line=""
    local old_len=
    local new_len=
    local total_len=
    local need_cr=1

    if [ "$LINE_OLD" == "" ]; then
        line=$(printf "%8s" "$new")
    else
        old_len=${#LINE_OLD}
        new_len=${#new}
        if [ $new_len -lt 8 ]; then
            new_len=8
        fi
        total_len=$(expr $old_len + $new_len)
        if [ $total_len -gt $col_size ]; then
            need_cr=0
            line=$(printf "%8s" "$new")
        else
            line=$(printf "%s%8s" "$LINE_OLD" "$new")
        fi
    fi
    LINE_OLD="$line"
    if [ "$need_cr" == "0" ]; then
        echo ""
    else
        echo -e "\r\c"
    fi
    echo -n "$line"
}

function print_snr() {
    local col_size=$1
    local snr=

    while true; do
        snr=$(mewsh rx_snr | grep snr | awk '{print$NF}')
        print_to_tail $snr $col_size
    done
    echo ""
}

function main() {
    local col_size=$1

    if [ $# -gt 1 -o "$1" == "-h" ]; then
        usage
        exit 0
    fi
    if [ "$col_size" == "" ]; then
        col_size=$DEFAULT_COL_SIZE
    fi
    print_snr $col_size
}

main $*
