#!/bin/bash

# 运行ubuntu 18.04的docker镜像，用于学习yocto 2.2.2

# 运行原始docker ubuntu 18.04镜像
docker run -it \
    -v /tmp/docker:/tmp/docker \
    --net=host \
    ubuntu:18.04 \
    /bin/bash
