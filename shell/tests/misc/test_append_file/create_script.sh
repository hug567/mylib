#!/bin/bash

function create_script_with_file() {
    local script_dir=$(cd $(dirname $BASH_SOURCE[0]); pwd)
    local cur_dir=$(pwd)
    local template="template.sh"
    local tmp_dir="tmp_patch"
    local tar_file="tmpxxyy.tar.gz"
    local output="shell_with_file.sh"

    if [ ! -d "${tmp_dir}" ]; then
        echo "there is no dir ${tmp_patch}"
        exit 1
    fi
    if [ ! -f "${script_dir}/${template}" ]; then
        echo "there is no file ${script_dir}/${template}"
        exit 2
    fi

    tar -zcvf ${tar_file} ${tmp_dir}
    cp ${script_dir}/${template} ${output}
    cat ${tar_file} >> ${output}
}

function main() {
    create_script_with_file
}

main $*
