#!/bin/bash

#docker run \
#    --net=host \
#    -v /tmp/docker:/tmp/docker \
#    -v /home/hx/code:/home/hx/code \
#    -v /home/hx/share:/home/hx/share \
#    -v /home/hx/temp:/home/hx/temp \
#    -v /home/hx/tools:/home/hx/tools \
#    -v /home/hx/workspace:/home/hx/workspace \
#    -v /run/dbus/system_bus_socket:/run/dbus/system_bus_socket:ro \
#    --hostname DockerUbuntu18 \
#    -it myubuntu18:v0.1 \
#    /bin/bash

# http://10.110.0.3:8080
#    myjenkins:v0.1

docker run \
    -u root --rm -d \
    -p 8080:8080 \
    -p 50000:50000 \
    -v /disk/sda:/disk/sda \
    -v /home/hx/code/jenkins/home:/var/jenkins_home \
    -v /home/hx/code/jenkins/root:/root \
    -v /var/run/docker.sock:/var/run/docker.sock \
    jenkins/jenkins:lts-jdk11
