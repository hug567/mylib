#!/bin/bash

LOGFMT="build_all_cpu1"

function log_with_level() {
    local level=$1
    local logs=${@:2}

    echo -e "[$(date '+%Y-%m-%d %H:%M:%S')][$LOGFMT][$level] $logs"
}

function log_info() {
    log_with_level "INFO" $*
}

function log_warn() {
    log_with_level "WARN" $*
}

function log_err() {
    log_with_level "ERROR" $*
}

function build_all_LC() {
    local top_dir=${1}
    local all_platforms=(
        "UWB"
    )
    local fmt="AutoX1V3_V3_3LC"
    local platform

    cd ${top_dir}/${fmt}
    log_info "[${fmt}]: -------------------------------------------------------"
    for platform in ${all_platforms[@]}; do
        log_info "[${fmt}][${platform}]: ------------------------------------"
        ./build.sh &> /tmp/"${platform}.log"
        if [ $? -ne 0 ]; then
            log_err "[${fmt}] build platform ${platform} failed"
            exit 1
        fi
        log_info "[${fmt}] build platform ${platform} success"
    done
}

function build_all_QQE() {
    local top_dir=${1}
    local all_platforms=(
        "QQE"
        "TEST"
    )
    local fmt="cpu1-QQE"
    local platform

    cd ${top_dir}/${fmt}
    log_info "[${fmt}]: -------------------------------------------------------"
    for platform in ${all_platforms[@]}; do
        log_info "[${fmt}][${platform}]: ------------------------------------"
        if [ "${platform}" == "QQE" ]; then
            ./build.sh &> /tmp/"${platform}.log"
        else
            ./build.sh ${platform} &> /tmp/"${platform}.log"
        fi
        if [ $? -ne 0 ]; then
            log_err "[${fmt}] build platform ${platform} failed"
            exit 1
        fi
        log_info "[${fmt}] build platform ${platform} success"
    done
}

function build_all_QQF() {
    local top_dir=${1}
    local all_platforms=(
        "QQF"
        "QQFC"
        "S450AT"
        "S450AY"
    )
    local fmt="cpu1-QQF"
    local platform

    cd ${top_dir}/${fmt}
    log_info "[${fmt}]: -------------------------------------------------------"
    for platform in ${all_platforms[@]}; do
        log_info "[${fmt}][${platform}]: ------------------------------------"
        ./build.sh ${platform} &> /tmp/"${platform}.log"
        if [ $? -ne 0 ]; then
            log_err "[${fmt}] build platform ${platform} failed"
            exit 1
        fi
        log_info "[${fmt}] build platform ${platform} success"
    done
}

function build_all_S400() {
    local top_dir=${1}
    local all_platforms=(
        "S400AT"
        "S100AT"
        "S450B"
    )
    local fmt="S400"
    local platform

    cd ${top_dir}/${fmt}
    log_info "[${fmt}]: -------------------------------------------------------"
    for platform in ${all_platforms[@]}; do
        log_info "[${fmt}][${platform}]: ------------------------------------"
        ./build.sh ${platform} &> /tmp/"${platform}.log"
        if [ $? -ne 0 ]; then
            log_err "[${fmt}] build platform ${platform} failed"
            exit 1
        fi
        log_info "[${fmt}] build platform ${platform} success"
    done
}

function build_all_S300B() {
    local top_dir=${1}
    local all_platforms=(
        "S300BT"
    )
    local fmt="RUV_300B"
    local platform

    cd ${top_dir}/${fmt}
    log_info "[${fmt}]: -------------------------------------------------------"
    for platform in ${all_platforms[@]}; do
        log_info "[${fmt}][${platform}]: ------------------------------------"
        ./build.sh &> /tmp/"${platform}.log"
        if [ $? -ne 0 ]; then
            log_err "[${fmt}] build platform ${platform} failed"
            exit 1
        fi
        log_info "[${fmt}] build platform ${platform} success"
    done
}

function build_all_S300E() {
    local top_dir=${1}
    local all_platforms=(
        "S300E"
    )
    local fmt="RUV_300E"
    local platform

    cd ${top_dir}/${fmt}
    log_info "[${fmt}]: -------------------------------------------------------"
    for platform in ${all_platforms[@]}; do
        log_info "[${fmt}][${platform}]: ------------------------------------"
        ./build.sh &> /tmp/"${platform}.log"
        if [ $? -ne 0 ]; then
            log_err "[${fmt}] build platform ${platform} failed"
            exit 1
        fi
        log_info "[${fmt}] build platform ${platform} success"
    done
}

function build_all_S300F() {
    local top_dir=${1}
    local all_platforms=(
        "S300F"
    )
    local fmt="RUV_300F"
    local platform

    cd ${top_dir}/${fmt}
    log_info "[${fmt}]: -------------------------------------------------------"
    for platform in ${all_platforms[@]}; do
        log_info "[${fmt}][${platform}]: ------------------------------------"
        ./build.sh &> /tmp/"${platform}.log"
        if [ $? -ne 0 ]; then
            log_err "[${fmt}] build platform ${platform} failed"
            exit 1
        fi
        log_info "[${fmt}] build platform ${platform} success"
    done
}

function build_all_cpu1() {
    local top_dir=${1}

    build_all_LC ${top_dir}
    build_all_QQE ${top_dir}
    build_all_QQF ${top_dir}
    build_all_S400 ${top_dir}
    build_all_S300B ${top_dir}
    build_all_S300E ${top_dir}
    build_all_S300F ${top_dir}
}

function main() {
    local cur_dir=$PWD
    local cpu1_dir=$cur_dir
    local bit_file="cpu1-QQF/ku_x2_wrapper_hw_platform_0/ku_x2_wrapper.bit"

    if [ -f "../AutoX1V3_V3_3LC/AutoX1V3_V3_3LC_wrapper.hdf" ]; then
        log_info "probably in one sub cpu1 repo root dir"
        cpu1_dir=$(cd $cur_dir/..; pwd)
    elif [ ! -f ${bit_file} ]; then
        log_err "[ERROR] current is not in all cpu1 repo root dir"
        exit 1
    fi

    build_all_cpu1 ${cpu1_dir}
    cd ${cur_dir}
}

main $*
