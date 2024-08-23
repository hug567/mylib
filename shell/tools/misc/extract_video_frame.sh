#!/bin/bash

function usage() {
    echo "Usage: $0 <video> <save_dir>   extract video frames"
    echo "   eg: $0 mmexport1718767257931.mp4 dir_20240619"
}

# 单位：秒
function get_video_duration() {
    local video=$1
    local time_s=

    time_s=$(ffprobe -v quiet -select_streams v -show_entries stream=duration -of csv="p=0" -i ${video})
    echo -n "${time_s%.*}"
}

function extract_frames() {
    local video=$1
    local save_dir=$2
    local time_s=
    local i=
    local name_sub=
    local file_name=

    time_s=$(get_video_duration ${video})
    echo "total time: ${time_s}s"
    pushd ${save_dir}
    # -r 5: 每秒提取5张图片
    ffmpeg -i ${video} -r 5 "output_%05d.jpg" &> /dev/null
    popd
    return
}

function main() {
    local video=$1
    local save_dir=$2
    local video_abs=

    if [ $# -ne 2 -o "$1" == "-h" ]; then
        usage
        exit 1
    fi

    if [ ! -f ${video} ]; then
        echo "there is no file ${video}"
        exit 1
    fi
    video_abs=$(realpath ${video})
    if [ ! -d ${save_dir} ]; then
        echo "there is no dir ${save_dir}"
        exit 1
    fi

    extract_frames ${video_abs} ${save_dir}
}

main $*
