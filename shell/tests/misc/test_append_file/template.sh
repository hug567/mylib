#!/bin/bash

function extract_append_file() {
    local scripts=${1}
    local tar_file="tmpxxyy.tar.gz"
    local unzip_dir="tmp_patch"
    local flag="c629ae10e99eaac8319317af07dc466ab9102e82"
    local num

    echo "scripts file: ${scripts}"

    num=$(grep -n -a "^${flag}$" ${scripts} | cut -d: -f1)
    let num=num+1
    tail -n +${num} ${scripts} > /tmp/${tar_file}

    cd /tmp
    if [ ! -f "${tar_file}" ]; then
        echo "there is no file: ${tar_file}"
        exit 1
    fi
    if [ -d "${unzip_dir}" ]; then
        rm -rf ${unzip_dir}
    fi
    tar -xvf ${tar_file}
    if [ ! -d "${unzip_dir}" ]; then
        echo "there is no dir ${unzip_dir}"
        exit 2
    fi
    cd ${unzip_dir}
    if [ ! -f "run.sh" ]; then
        echo "there is no file run.sh"
        exit 3
    fi
    ./run.sh
}

function main() {
    local cur_file=$0

    extract_append_file ${cur_file}
}

main $*
exit $?

c629ae10e99eaac8319317af07dc466ab9102e82
