#!/bin/bash
# 2024-04-10

WORK_DIR="/mnt/sdb/jenkins/source_code"
IMAGES_DIR="/mnt/sdb/jenkins/images"
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

    if [ "$platform" = "default" ]; then
        $script
    else
        $script $platform
    fi
    return $?
}

function build_yocto() {
    local platform=$1
    local plat_image_dir=$2
    local image_dir=$WORK_DIR/yocto/images/linux

    if ! build_petalinux yocto $platform; then
        log_err "build $platform yocto failed"
        exit 1
    fi
    cp $image_dir/BOOT.BIN $plat_image_dir
    cp $image_dir/image.ub $plat_image_dir
    cp $image_dir/rootfs.tar.bz2 $plat_image_dir
}

function build_mkpart() {
    local platform=$1
    local plat_image_dir=$2
    local image_dir=$WORK_DIR/ramfs/yocto-mkpart/images/linux

    if ! build_petalinux ramfs/yocto-mkpart $platform; then
        log_err "build $platform ramfs/yocto-mkpart failed"
        exit 1
    fi
    cp $image_dir/BOOT-MKPART.BIN $plat_image_dir
    cp $image_dir/image-mkpart.ub $plat_image_dir
}

function build_ramfs() {
    local platform=$1
    local plat_image_dir=$2
    local image_dir=$WORK_DIR/ramfs/yocto-ramfs/images/linux

    build_petalinux ramfs/yocto-ramfs $platform
    if ! build_petalinux ramfs/yocto-ramfs $platform; then
        log_err "build $platform ramfs/yocto-ramfs failed"
        exit 1
    fi
    cp $image_dir/image-ram.ub $plat_image_dir
}

function build_one_platform() {
    local platform=$1
    local images_dir=$2
    local plat_image_dir=$images_dir/$platform

    log_info "will build platform: $platform ----------------------------------"
    if [ ! -d $plat_image_dir ]; then
        mkdir -p $plat_image_dir
    fi
    build_yocto $platform $plat_image_dir
    build_mkpart $platform $plat_image_dir
    build_ramfs $platform $plat_image_dir
}

# default, QQF, s300, ...
function build_all_platform() {
    local work_dir=$WORK_DIR
    local images_dir=$IMAGES_DIR/$(date '+%Y%m%d_%H%M%S')

    log_info "will build all platform images"
    cd $work_dir
    log_info "pwd: $(pwd)"
    log_info "os-release: -----------------------------------------------------"
    cat /etc/os-release
    ls -la /

    build_one_platform "default" $images_dir
    build_one_platform "QQF" $images_dir
    build_one_platform "s300" $images_dir
}

function main() {
    build_all_platform
    log_info "finish building all images in docker"
}

main $*
