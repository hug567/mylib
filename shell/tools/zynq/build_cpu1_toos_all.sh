#!/bin/bash

function build_all_platforms() {
    local all_platforms=(
        "QQE"
        "QQF"
        "QQFC"
        "S100A"
        "S400A"
        "S300BT"
        "S300F"
        "S450A"
        "UWB"
        "TEST"
        "S300E"
        "S450B"
        "DEMO"
        "KU_2D_FDD_RESAS"
    )
    local platform

    for platform in ${all_platforms[@]}; do
        echo "[INFO][${platform}]: --------------------------------------------"
        if [ -d build ]; then
            rm -rf build
        fi
        ./scripts/build.sh ${platform} &> "/tmp/cpu1_tools_${platform}.log"
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
    local flag_file="include/share.h"

    if [ ! -f ${flag_file} ]; then
        echo "[ERROR] current is not in cpu1_tools repo"
        exit 1
    fi

    build_all_platforms
}

main $*
