#!/bin/bash

docker run \
    --net=host \
    -v /tmp/docker:/tmp/docker \
    -v /home/hx/code:/home/hx/code \
    -v /home/hx/share:/home/hx/share \
    -v /home/hx/temp:/home/hx/temp \
    -v /home/hx/tools:/home/hx/tools \
    -v /home/hx/workspace:/home/hx/workspace \
    -it myubuntu16:v0.1 \
    /bin/bash
