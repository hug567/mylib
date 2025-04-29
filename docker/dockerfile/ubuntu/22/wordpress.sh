#!/bin/bash
# Create: 2025-04-28 13:21:47

function usage() {
    echo "Usage: "
}

function docker_run() {
    local image=$1
    local docker_home="/home/wordpress"

    # 在容器中运行systemd
    docker run \
        --net=host \
        --privileged \
        --cgroupns "host" \
        -v /sys/fs/cgroup:/sys/fs/cgroup:ro \
        -v /tmp/docker:/tmp/docker \
        -v ${HOME}/code:${docker_home}/code \
        -v ${HOME}/share:${docker_home}/share \
        -v ${HOME}/temp:${docker_home}/temp \
        -v ${HOME}/tools:/${docker_home}/tools \
        -v ${HOME}/repo:/${docker_home}/repo \
        -d ${image}
}

function main() {
    docker_run wordpress:v0.1
}

main $*
