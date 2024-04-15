#!/bin/bash
# 接受从jenkins传入的参数
# 2024-04-15

function main() {
    local download_code=$1

    echo "download_code: $download_code"
    if [ "$download_code" = "true" ]; then
        echo "need to download the code again"
    else
        echo "no need to download the code again"
    fi
}

main $*
