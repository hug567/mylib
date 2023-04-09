#!/bin/bash

CUR_SCRIPT_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export MYLIB=$(cd ${CUR_SCRIPT_DIR}/../../; pwd)
source ${MYLIB}/shell/yocto/common.sh

usage() {
    log_info "$0 <remote>     push all branches to remote"
}

push_all_branches() {
    local remote=$1
    local branches=$(git branch | cat)
    echo "$branches" | while read branch
    do
        local br=${branch}
        if [ "${br:0:2}" = "* " ]; then
            br=${br:2}
        fi
        if [ -n "$br" ]; then
            log_info "will push branch to $remote: $br"
            git checkout $br
            log_info "current branch: $(git branch | cat | grep "^* ")"
            git push $remote HEAD:$br
        fi
    done
}

main() {
    if [ $# != 1 ]; then
        usage
        exit
    fi
    local remote=$1
    push_all_branches $remote
}

main $*
