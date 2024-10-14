#!/bin/bash

function main() {
    local image="rhosoon_ubuntu_18:v0.7"

    docker run -it \
        --user rhosoon -w /home/rhosoon \
        -v /disk:/disk \
        -v /mnt/sdb:/mnt/sdb \
        -v /opt/pkg:/opt/pkg \
        -v /opt/Xilinx:/opt/Xilinx \
        -v /tmp/docker:/tmp/docker \
        -v ${HOME}/repo:/home/rhosoon/repo \
        -v ${HOME}/code:/home/rhosoon/code \
        -v ${HOME}/temp:/home/rhosoon/temp \
        -v ${HOME}/tools:/home/rhosoon/tools \
        -v ${HOME}/share:/home/rhosoon/share \
        --net=host \
        ${image} \
        /bin/bash
}

main $*
