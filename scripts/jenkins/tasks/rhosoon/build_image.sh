#!/bin/bash
# 2024-04-10

LOGFMT="build_image"
WORK_DIR="/opt/jenkins/source_code"
CUR_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export PATH="$HOME/tools/git-repo:$PATH"

function log_with_level() {
    local level=$1
    local logs="${@:2}"
    echo -e "[$(date '+%Y-%m-%d %H:%M:%S')][$LOGFMT][$level] $logs"
}

function log_info() {
    log_with_level "INFO" "$*"
}

function log_warn() {
    log_with_level "WARN" "$*"
}

function log_err() {
    log_with_level "ERROR" "$*"
}

function run_cmd_and_check() {
    local cmd="$*"
    local ret=

    $cmd
    ret=$?
    if [ $ret -ne 0 ]; then
        log_info "run cmd failed: [$cmd]"
        exit $ret
    fi
}

function run_until_success() {
    local max_times=$1
    local cmd="${@:2}"
    local i=
    local ret=

    for i in $(seq 1 $max_times); do
        log_info "will run cmd($i): [bash -c \"$cmd\"]"
        bash -c "${cmd}"
        ret=$?
        if [ $ret -eq 0 ]; then
            return 0
        fi
    done
    log_err "run cmd with times $i failed: [bash -c \"$cmd\"]"
    exit $ret
}

function repo_download_code() {
    local work_dir=$1

    if [ ! -d $work_dir ]; then
        mkdir -p $work_dir
    fi
    cd $work_dir
    log_info "will clean dir $work_dir"
    rm -rf $(ls -1A)
    log_info "will download code to dir $work_dir"
    run_until_success 10 "repo init -u http://192.168.99.221:3000/Rhosoon_RD/manifest.git --repo-url=http://192.168.99.221:3000/Rhosoon_RD/git-repo.git --repo-rev=main --no-clone-bundle"
    run_until_success 10 "repo sync"
    run_until_success 10 "repo forall -c 'git lfs pull'"
    run_until_success 10 "repo start main --all"
    run_until_success 10 "repo status | cat"
    log_info "finish download code to dir $work_dir"
}

function delete_old_docker_container() {
    local ids=

    ids=$(docker ps -a | grep rhosoon_docker_ | awk '{print$1}')
    if [ "$ids" = "" ]; then
        return
    fi
    echo "$ids" | while read id; do
        log_info "will stop and rm container: $id"
        docker stop $id
        docker rm $id
    done
}

function delete_container_by_name() {
    local name=$1
    local id=

    id=$(docker ps -a | grep "$name" | head -n 1 | awk '{print$1}')
    if [ "$id" != "" ]; then
        log_info "will stop and rm container: $name/$id"
        docker stop $id
        docker rm $id
    fi
}

function launch_docker() {
    local image="rhosoon_ubuntu_18:v0.5"
    local name="rhosoon_docker_$(date '+%Y%m%d%H%M%S')"

    log_info "will launch docker with name: $name"
    PS1="[host] $ "
    echo $PS1
expect <<EOF
    set timeout 43200
    spawn docker run -it \
        --user rhosoon -w /home/rhosoon \
        -v /mnt/sdb:/mnt/sdb \
        -v /opt/pkg:/opt/pkg \
        -v /opt/jenkins:/opt/jenkins \
        -v /tmp/docker:/tmp/docker \
        -v ${HOME}/repo:/home/rhosoon/repo \
        -v ${HOME}/code:/home/rhosoon/code \
        -v ${HOME}/temp:/home/rhosoon/temp \
        -v ${HOME}/tools:/home/rhosoon/tools \
        -v ${HOME}/share:/home/rhosoon/share \
        --net=host \
        --name=${name} \
        ${image} \
        /bin/bash
    sleep 5
    send "\rPS1='\[\\\u@\\\h\] \\\w $ '\r"
    expect {
        "\[rhosoon@" { send "/tmp/docker/build_image_in_docker.sh\r"}
        timeout { puts "docker build timeout"; exit 127 }
    }
    expect {
        "ERROR: Failed to build project" { puts "build images failed"; exit 127 }
        "finish building all images in docker" {}
        timeout { puts "docker build timeout"; exit 127 }
    }
EOF

    delete_container_by_name $name
}

function main() {
    local download_code=$1

    log_info "host net: -------------------------------------------------------"
    ifconfig -a
    log_info "-----------------------------------------------------------------"
    if [ "$download_code" = "true" ]; then
        repo_download_code $WORK_DIR
    fi
    cp $CUR_DIR/build_image_in_docker.sh /tmp/docker
    launch_docker
}

main $*
