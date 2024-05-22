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
    local sub="path=\""
    local start=$(awk -v a="${line}" -v b="${sub}" 'BEGIN{print index(a,b)}')
    local next=$(expr ${start} + ${#sub} - 1)
    local tail=${line[@]:${next}}
    local start=$(awk -v a="${tail}" -v b="\"" 'BEGIN{print index(a,b)}')
    local len=$(expr ${start} - 1)
    local path=${tail[@]:0:${len}}
    echo -n "${path}"
}

function get_repo_revision() {
    local line="$*"
    local sub="revision=\""
    local start=$(awk -v a="${line}" -v b="${sub}" 'BEGIN{print index(a,b)}')
    local next=$(expr ${start} + ${#sub} - 1)
    local tail=${line[@]:${next}}
    local start=$(awk -v a="${tail}" -v b="\"" 'BEGIN{print index(a,b)}')
    local len=$(expr ${start} - 1)
    local revision=${tail[@]:0:${len}}
    echo -n "${revision}"
}

function get_current_detached_hash() {
    local abs_path=$1
    local detached_hash=

    pushd ${abs_path} &> /dev/null
    detached_hash=$(git branch | grep "\*" | grep detached | awk '{print$NF}')
    detached_hash=(${detached_hash//)/ })
    if [ "${detached_hash}" == "" ]; then
        popd &> /dev/null
        return
    fi
    detached_hash=$(git rev-parse ${detached_hash})
    popd &> /dev/null
    echo -n "${detached_hash}"
}

function get_current_branch() {
    local abs_path=$1
    local branch=

    pushd ${abs_path} &> /dev/null
    branch=$(git branch | grep "\*" | awk '{print$NF}')
    popd &> /dev/null
    echo -n "${branch}"
}

function get_current_revision() {
    local abs_path=$1
    local detached_hash=
    local branch=

    pushd ${abs_path} &> /dev/null
    detached_hash=$(get_current_detached_hash ${abs_path})
    if [ "${detached_hash}" != "" ]; then
        echo -n "${detached_hash}"
        popd &> /dev/null
        return
    fi
    branch=$(get_current_branch ${abs_path})
    popd &> /dev/null
    echo -n "${branch}"
}

function checkout_one_repo() {
    local abs_path=$1
    local revision=$2
    local cur_revision=

    pushd ${abs_path} &> /dev/null
    if [ ! -d .git ]; then
        log_error "no .git dir in: ${abs_path}"
        popd &> /dev/null
        return
    fi
    cur_revision=$(get_current_revision ${abs_path})
    if [ "${revision}" == "${cur_revision}" ]; then
        log_info "current is already at revision: ${revision}"
        popd &> /dev/null
        return
    fi
    log_info "will checkout to revision: ${revision}"
    git checkout ${revision}
    popd &> /dev/null
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
        log_info "-------------------------------------------------------------"
        path=$(get_repo_path "${line}")
        revision=$(get_repo_revision "${line}")
        abs_path=$(cd ${top_dir}/${path}; pwd)
        log_info "path: ${path}, revision: ${revision}"
        checkout_one_repo ${abs_path} ${revision}
    done
}

function main() {
    local top_dir=${PWD}
    local manifest_file="${top_dir}/.repo/manifests/default.xml"

    if [ ! -f ${manifest_file} ]; then
        log_error "no manifest file: $manifest_file"
        exit 1
    fi
    repo_checkout $top_dir $manifest_file
}

main $*
