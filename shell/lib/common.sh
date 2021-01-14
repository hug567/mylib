#!/bin/bash

BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
PURPLE="\033[35m"
SKYBLUE="\033[36m"
WHITE="\033[37m"
RESET="\033[0m"

CPU_THREAD_NUM=`cat /proc/cpuinfo | grep "processor" | wc -l`

log_info() {
    echo -e "[$(date +"%Y-%m-%d %H:%M:%S")][INFO ] $1"
}

log_error() {
    echo -e "[$(date +"%Y-%m-%d %H:%M:%S")][ERROR] $1"
}
