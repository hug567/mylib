#!/bin/bash
# 2024-04-10

WORK_DIR="/opt/jenkins/source_code"
IMAGES_ROOT_DIR="/opt/jenkins/images"
LOGFMT="build_image_in_docker"

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

function build_petalinux() {
    local project=$1
    local platform=$2
    local work_dir=$WORK_DIR
    local script=

    log_info "will build $platform $project -----------------------------------"
    cd $work_dir/$project
    log_info "pwd: $(pwd)"
    if [ ! -f config.project ]; then
        log_err "current is not in yocto dir"
        exit 1
    fi
    rm -rf build
    git clean -fdx

    if [[ $project =~ ^ramfs* ]]; then
        script="./build.sh"
    else
        script="../build.sh"
    fi

    $script $platform
    return $?
}

function build_yocto() {
    local platform=$1
    local plat_images_dir=$2
    local images_dir=$WORK_DIR/yocto/images/linux

    if ! build_petalinux yocto $platform; then
        log_err "build $platform yocto failed"
        exit 1
    fi
    cp $images_dir/BOOT.BIN $plat_images_dir
    cp $images_dir/image.ub $plat_images_dir
    cp $images_dir/rootfs.tar.bz2 $plat_images_dir
}

function build_mkpart() {
    local platform=$1
    local plat_images_dir=$2
    local images_dir=$WORK_DIR/ramfs/yocto-mkpart/images/linux

    if ! build_petalinux ramfs/yocto-mkpart $platform; then
        log_err "build $platform ramfs/yocto-mkpart failed"
        exit 1
    fi
    cp $images_dir/BOOT-MKPART.BIN $plat_images_dir
    cp $images_dir/image-mkpart.ub $plat_images_dir
}

function build_ramfs() {
    local platform=$1
    local plat_images_dir=$2
    local images_dir=$WORK_DIR/ramfs/yocto-ramfs/images/linux

    build_petalinux ramfs/yocto-ramfs $platform
    if ! build_petalinux ramfs/yocto-ramfs $platform; then
        log_err "build $platform ramfs/yocto-ramfs failed"
        exit 1
    fi
    cp $images_dir/image-ram.ub $plat_images_dir
}

function build_one_platform() {
    local platform=$1
    local use_for=$2 # all/yocto/ramfs/mkpart
    local images_dir=$3
    local plat_images_dir=$images_dir/$platform

    log_info "will build platform: $platform ----------------------------------"
    if [ ! -d $plat_images_dir ]; then
        mkdir -p $plat_images_dir
    fi
    if [ "$use_for" = "yocto" ]; then
        build_yocto $platform $plat_images_dir
    elif [ "$use_for" = "ramfs" ]; then
        build_ramfs $platform $plat_images_dir
    elif [ "$use_for" = "mkpart" ]; then
        build_mkpart $platform $plat_images_dir
    else
        build_yocto $platform $plat_images_dir
        build_ramfs $platform $plat_images_dir
        build_mkpart $platform $plat_images_dir
    fi
}

# QQE, QQF, S300, ...
function build_all_platforms() {
    local use_for=$1
    local images_dir=$2

    build_one_platform "QQE" $use_for $images_dir
    build_one_platform "QQF" $use_for $images_dir
    build_one_platform "S300" $use_for $images_dir
}

function print_host_info() {
    log_info "host info: ------------------------------------------------------"
    cat /etc/os-release
    ls -la /
    ifconfig -a
    log_info "host info: ------------------------------------------------------"
}

function main() {
    local platform=$1
    local use_for=$2
    local work_dir=$WORK_DIR
    local images_date=$(date '+%Y%m%d_%H%M%S')
    local images_dir=$IMAGES_ROOT_DIR/$images_date
    local myip=$(ifconfig | grep 10.110.0 | head -n 1 | awk '{print$2}')

    print_host_info
    cd $work_dir
    log_info "work_dir: $work_dir"
    if [ "$platform" = "" -o "$platform" = "all" ]; then
        log_info "will build all platform images"
        build_all_platforms $use_for $images_dir
    else
        log_info "will only build one platform images: $platform"
        build_one_platform $platform $use_for $images_dir
    fi
    log_info "images: http://${myip}:9008/$images_date"
    log_info "finish building all images in docker"
}

main $*
