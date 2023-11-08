#!/bin/bash

export FLASK_DEBUG=1
export FLASK_APP=main.py

function ip_exist() {
    local ip=$1
    local ret=$(ifconfig | grep "$ip")

    if [ "$ret" == "" ]; then
        return 1
    fi
    return 0
}

function main() {
    local ip=""
    local ip_addr=(
        "10.110.0.3"
        "172.20.115.98"
    )
    for ip in ${ip_addr[@]}; do
        if ip_exist $ip; then
            flask run -h $ip -p 9200
        fi
    done
}

main $*
