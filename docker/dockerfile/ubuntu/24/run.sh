#!/bin/bash
# 2024-09-10

function usage() {
    echo "Usage: "
}

function docker_run() {
    local image=$1
    local docker_home="/home/hx"

    docker run \
        --net=host \
        -v /tmp/docker:/tmp/docker \
        -v ${HOME}/code:${docker_home}/code \
        -v ${HOME}/share:${docker_home}/share \
        -v ${HOME}/temp:${docker_home}/temp \
        -v ${HOME}/tools:/${docker_home}/tools \
        -v ${HOME}/repo:/${docker_home}/repo \
        -it ${image} \
        /bin/bash
}

function main() {
    docker_run myubuntu24:v0.1
}

main $*
