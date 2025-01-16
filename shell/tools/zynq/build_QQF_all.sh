#!/bin/bash

function build_all_platforms() {
    local all_platforms=(
        "QQF"
        "QQFC"
        "QQFT"
        "QQFTC"
        "S450AT"
        "S450AY"
        "S450BT"
    )
    local platform

    for platform in ${all_platforms[@]}; do
        echo "[INFO][${platform}]: --------------------------------------------"
        ./build.sh ${platform} &> /tmp/"${platform}.log"
        if [ $? -ne 0 ]; then
            echo "[ERROR] build platform ${platform} failed"
            exit 1
        fi
        echo "[INFO] build platform ${platform} success"
    done
    echo "[INFO] build all platforms success: ${all_platforms[@]}"
}

function main() {
    local cur_dir=$PWD
    local bit_file="ku_x2_wrapper_hw_platform_0/ku_x2_wrapper.bit"

    if [ ! -f ${bit_file} ]; then
        echo "[ERROR] current is not in cpu1-QQF repo"
        exit 1
    fi

    build_all_platforms
}

main $*
