#!/bin/bash
# 2024-04-10

LOGFMT="tag_to_commit"

function log_with_level() {
    local level=$1
    local logs="${@:2}"
    echo -e "[$(date '+%Y-%m-%d %H:%M:%S')][$LOGFMT][$level] $logs"
}

function log_info() {
    log_with_level "INFO" "$*"
}

function log_warn() {
    log_with_level "WARN" "$*"
}

function log_err() {
    log_with_level "ERROR" "$*"
}

function download_code() {
    local repo_dir=$1
    local remote_url="http://192.168.99.221:3000/Rhosoon_RD/manifest.git"

    if [ -d $repo_dir ]; then
        rm -rf $repo_dir
        mkdir -p $repo_dir
    fi
    git clone $remote_url -b main $repo_dir &> /dev/null
}

function there_is_same_tag() {
    local repo_dir=$1
    local maybe_tag=$2
    local tag=
    local all_tags=

    cd $repo_dir
    all_tags=$(git tag)
    echo "$all_tags" | while read tag; do
        if [ "$tag" == "$maybe_tag" ]; then
            echo "$tag"
            return
        fi
    done
}

function is_tag() {
    local repo_dir=$1
    local maybe_tag=$2
    local same_tag=

    same_tag=$(there_is_same_tag $repo_dir $maybe_tag)
    if [ "$same_tag" != "" ]; then
        return 0
    fi
    return 1
}

function tag_to_commit() {
    local tag=$1
    local repo_dir="/tmp/manifest"
    local commit=
    local commit_short=
    local same_tag=

    download_code $repo_dir
    if ! is_tag $repo_dir $tag; then
        return
    fi

    cd $repo_dir
    commit_short=$(git log --oneline --decorate | grep "tag:" | grep $tag | awk '{print$1}')
    if [ "$commit_short" == "" ]; then
        return
    fi
    commit=$(git show $commit_short | head -n 1 | awk '{print$NF}')
    echo -n "$commit"
}

function main() {
    local tag=$1
    local commit=

    commit=$(tag_to_commit $tag)
    log_info "tag: $tag, main commit: $commit"

}

main $*
