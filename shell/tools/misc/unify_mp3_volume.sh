#!/bin/bash

function handle_mp3_files() {
    local src_dir="origin"
    local dst_dir="handled"
    local all_files file_num i file count=1

    if [ ! -d ${src_dir} ] || [ ! -d ${dst_dir} ]; then
        echo "there is no dir ${src_dir} or ${dst_dir}"
        exit 1
    fi
    file_num=$(cd ${src_dir}; ls -1 *.mp3 | wc -l)
    echo "file_num: ${file_num}"
    for i in $(seq ${file_num} -1 1); do
        file="$(cd ${src_dir}; ls -1 *.mp3 | sort | tail -n ${i} | head -n 1)"
        echo "file[${count}]: ${file} --------------------------------------- #"
        if [ -f "${dst_dir}/${file}" ]; then
            rm "${dst_dir}/${file}"
        fi
        #ffmpeg -i "${src_dir}/${file}" -af loudnorm=I=-16:LRA=11:TP=-1.5 "${dst_dir}/${file}" &> /dev/null
        ffmpeg -i "${src_dir}/${file}" -af loudnorm=I=-13:LRA=9:TP=-1.0 "${dst_dir}/${file}" &> /dev/null
        #ffmpeg -i "${src_dir}/${file}" -af loudnorm=I=-10:LRA=9:TP=-1.0 "${dst_dir}/${file}" &> /dev/null
        if [ $? -ne 0 ]; then
            echo "handle flile fail: ${src_dir}/${file} <<<<<<<<<<<<<<<<<<<<<<<"
            exit 1
        fi
        let count=count+1
        if [ ${count} -gt 1000000 ]; then
            exit 0
        fi
    done
}

function main() {
    handle_mp3_files
}

main $*
