#!/bin/bash

function usage() {
    echo "Usage: $0 work                     run in work computer"
    echo "Usage: $0 personal                 run in work personal computer wsl2"
}

function run_in_work_compute() {
    docker run \
        --net=host \
        -v ${HOME}/code:/home/hx/code \
        -v ${HOME}/share:/home/hx/share \
        -v ${HOME}/temp:/home/hx/temp \
        -v ${HOME}/tools:/home/hx/tools \
        -v ${HOME}/repo:/home/hx/repo \
        --hostname DockerUbuntu18 \
        -it myubuntu18:v0.1 \
        /bin/bash
}

function run_in_personal_wsl2() {
    docker run \
        --net=host \
        -v ${HOME}/code:/home/hx/code \
        -v ${HOME}/temp:/home/hx/temp \
        -v ${HOME}/tools:/home/hx/tools \
        --hostname DockerUbuntu18 \
        -it myubuntu18:v0.1 \
        /bin/bash
}

function main() {
    local machine=$1

    if [ "${machine}" == "work" ]; then
        run_in_work_compute
    elif [ "${machine}" == "personal" ]; then
        run_in_personal_wsl2
    else
        usage
        exit
    fi
}

main $*
