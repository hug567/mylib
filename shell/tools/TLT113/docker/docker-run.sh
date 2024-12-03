#!/bin/bash

function main() {
    local image="tl_ubuntu_18:v0.1"

    docker run -it \
        -v /disk:/disk \
        -v /mnt/sdb:/mnt/sdb \
        -v /opt/pkg:/opt/pkg \
        -v /tmp/docker:/tmp/docker \
        -v ${HOME}/repo:/home/t113/repo \
        -v ${HOME}/code:/home/t113/code \
        -v ${HOME}/temp:/home/t113/temp \
        -v ${HOME}/tools:/home/t113/tools \
        -v ${HOME}/share:/home/t113/share \
        --net=host \
        ${image} \
        /bin/bash
}

main $*
