#!/bin/bash

function usage() {
    echo "Usage: $0 <repo_top> <dst_dir>    collect image files to dst dir"
}

function collect_one_file() {
    local file=${1}
    local dst_dir=${2}

    if [ ! -f ${file} ]; then
        echo "no file ${file}"
        return
    fi
    if [ ! -d ${dst_dir} ]; then
        echo "no dir ${dst_dir}"
        return
    fi
    echo "will cp ${file} to ${dst_dir}"
    cp ${file} ${dst_dir}
}

function collect_yocto_images() {
    local images_dir=${1}
    local dst_dir=${2}

    collect_one_file ${images_dir}/BOOT.BIN ${dst_dir}
    collect_one_file ${images_dir}/image.ub ${dst_dir}
    collect_one_file ${images_dir}/rootfs.tar.bz2 ${dst_dir}
}

function collect_ram_images() {
    local images_dir=${1}
    local dst_dir=${2}

    collect_one_file ${images_dir}/image-ram.ub ${dst_dir}
}

function collect_mkpart_images() {
    local images_dir=${1}
    local dst_dir=${2}

    collect_one_file ${images_dir}/BOOT-MKPART.BIN ${dst_dir}
    collect_one_file ${images_dir}/image-mkpart.ub ${dst_dir}
}

function collect_all_images() {
    local repo_top=${1}
    local dst_dir=${2}

    if [ ! -d ${repo_top} ]; then
        echo "no dir: ${repo_top}"
        exit 1
    fi
    if [ ! -d ${dst_dir} ]; then
        echo "no dir: ${dst_dir}"
        exit 1
    fi

    collect_yocto_images ${repo_top}/yocto/images/linux ${dst_dir}
    collect_ram_images ${repo_top}/ramfs/yocto-ramfs/images/linux ${dst_dir}
    collect_mkpart_images ${repo_top}/ramfs/yocto-mkpart/images/linux ${dst_dir}
}

function main() {
    local repo_top=${1}
    local dst_dir=${2}

    if [ $# != 2 ]; then
        usage
        exit 1
    fi

    collect_all_images ${repo_top} ${dst_dir}
}

main $*
