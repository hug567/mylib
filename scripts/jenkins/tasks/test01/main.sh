#!/bin/bash
# 2023-07-06

# script for jenkins pipeline task test01
# jenkins will run this script in some jenkins node

set +x

function delete_container() {
    sudo docker ps -a
    local ids=$(sudo docker ps -q)
    if [ "$ids" != "" ]; then
        sudo docker stop $ids
    fi
    local ids=$(sudo docker ps -a -q)
    if [ "$ids" != "" ]; then
        sudo docker rm $ids
    fi
    sudo docker ps -a
}

function load_docker_image() {
    sudo docker images
    local ids=$(sudo docker images myubuntu:v1.0 -q)
    if [ "$ids" == "" ]; then
        scp hx@10.110.192.42:/home/hx/temp/jenkins/myubuntu.tar .
        sudo docker load -i myubuntu.tar
    fi
}

function run_docker() {
    sudo docker run --user hx -w /home/hx --net=host -d -v $PWD:/data -it myubuntu:v1.0 /bin/bash
    sleep 3
    local id=$(sudo docker ps | grep myubuntu | grep v1.0 | awk '{print$1}')
    if [ "$id" == "" ]; then
        return
    fi
    # run cmd in docker
    sudo docker exec $id 'sh' '-c' 'cat /etc/os-release'
    sudo docker exec $id 'sh' '-c' 'ls -l /data'
    sudo docker exec $id 'sh' '-c' 'env'
    sudo docker exec $id 'sh' '-c' '/data/mylib/scripts/jenkins/tasks/test01/docker.sh'
}

function main() {
    local build_number=$1
    echo "build_number: $build_number"
    echo "cur dir: $(pwd)"
    sudo gpasswd -a $USER docker && newgrp docker
    delete_container
    load_docker_image
    run_docker
}

main $*
