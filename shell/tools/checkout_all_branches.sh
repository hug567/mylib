#!/bin/bash

CUR_SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${CUR_SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/yocto/common.sh

checkout_all_branches() {
    local branches=$(git branch -a | cat | grep "remotes\/origin" | grep -v "HEAD")
    echo "$branches" | while read branch
    do
        local br=${branch:15} # 去除头部remotes/origin/
        if [ -n "$br" ]; then
            log_info "will checkout branch: $br"
            git checkout $br
        fi
    done
}

main() {
    checkout_all_branches
}

main $*
