#!/bin/bash
# 2024-04-10

function run_jenkins_docker() {
    docker run \
        -u root --rm -d \
        -p 8080:8080 \
        -p 50000:50000 \
        -v /mnt/sdb:/mnt/sdb \
        -v /opt/pkg:/opt/pkg \
        -v /tmp/docker:/tmp/docker \
        -v $HOME/repo:/root/repo \
        -v $HOME/code:/root/code \
        -v $HOME/temp:/root/temp \
        -v $HOME/tools:/root/tools \
        -v $HOME/share:/root/share \
        -v $HOME/code/jenkins/home:/var/jenkins_home \
        -v $HOME/code/jenkins/root:/root \
        -v /var/run/docker.sock:/var/run/docker.sock \
        myjenkins:v0.3
        #jenkins/jenkins:lts-jdk11
}

function main() {
    run_jenkins_docker
}

main $*
