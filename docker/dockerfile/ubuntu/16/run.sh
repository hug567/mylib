#!/bin/bash

docker run --net=host -v /tmp/docker:/tmp/docker -it myubuntu16:v0.1 /bin/bash
