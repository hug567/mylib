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
    for i in $(seq 1 ${time_s}); do
        name_sub=$(printf "%03d" ${i})
        file_name="output_${name_sub}.jpg"
        echo "will extract image: ${file_name}"
        ffmpeg -i ${video} -ss ${i} -vframes 1 "${save_dir}/${file_name}" &> /dev/null
    done
}

function main() {
    local video=$1
    local save_dir=$2

    if [ $# -ne 2 -o "$1" == "-h" ]; then
        usage
        exit 1
    fi

    if [ ! -f ${video} ]; then
        echo "there is no file ${video}"
        exit 1
    fi
    if [ ! -d ${save_dir} ]; then
        echo "there is no dir ${save_dir}"
        exit 1
    fi

    extract_frames ${video} ${save_dir}
}

main $*
