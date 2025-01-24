#!/bin/bash

function usage() {
    echo "Usage: $0 <image> <user>         run docker container"
    echo "   eg: $0 myubuntu22:v0.2 hx"
}

function run_docker() {
    local image="$1"
    local user=$2

    docker run -it \
        --user ${user} -w /home/${user} \
        -v /tmp/docker:/tmp/docker \
        -v ${HOME}/repo:/home/${user}/repo \
        -v ${HOME}/code:/home/${user}/code \
        -v ${HOME}/temp:/home/${user}/temp \
        -v ${HOME}/tools:/home/${user}/tools \
        -v ${HOME}/share:/home/${user}/share \
        --net=host \
        ${image} \
        /bin/bash
}

function main() {
    local image=$1
    local user=$2

    if [ $# -ne 2 -o "$1" == "-h" ]; then
        usage
        exit 1
    fi
    run_docker ${image} ${user}
}

main $*
