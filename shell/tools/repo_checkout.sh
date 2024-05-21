#!/bin/bash
# 根据repo manifest文件切换各仓库到对应分支

export SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/lib/common.sh

function usage() {
    log_info "$0         checkout according manifest file"
}

function get_repo_path() {
    local line="$*"
    echo "${line}"
}

function get_repo_revision() {
    local line="$*"
}

function checkout_one_repo() {
    local path=$1
    local revision=$2
}

function repo_checkout() {
    local top_dir=$1
    local manifest_file=$2
    local repo_lines=$(cat ${manifest_file} | grep "project")
    local line=
    local path=
    local abs_path=
    local revision=

    echo "${repo_lines}" | while read line; do
        path=$(get_repo_path "${line}")
        revision=$(get_repo_revision "${line}")
        abs_path=$(cd ${top_dir}/${path}; pwd)
        log_info "path: ${path}"
        log_info "revision: ${revision}"
    done
}

function main() {
    local top_dir=${PWD}
    local manifest_file="${top_dir}/.repo/manifests/default.xml"

    if [ ! -f ${manifest_file} ]; then
        log_err "no manifest file: $manifest_file"
        exit 1
    fi
    repo_checkout $top_dir $manifest_file
}

main $*
