#!/usr/bin/bash

# lsab
# lsab .
# lsab ./
# lsab ./*
# lsab dir
# lsab dir/*
# lsab file.txt
# lsab file.txt dir1 dir2
function lsab() {
    local ret=
    local dir=
    local abs=
    if [ $# = 0 ]; then
        echo "$(pwd)/"
        ret=$(ls)
        if [ "$ret" = "" ]; then
            ret="."
        fi
    else
        ret="$*"
    fi
    ret=$(echo "$ret" | awk -F ' ' '{for (i = 1; i <= NF; i++) print $i}')
    echo "$ret" | while read f
    do
        if [ -d $f ]; then
            dir=$(cd $f; pwd)
            echo $dir
            continue
        fi
        if [ ${f:0:1} = '/' -o ${f:0:1} = '~' ]; then
            abs="$f"
        else
            abs=$(cd $(dirname $f); pwd)/$(basename $f)
        fi
        if [ -e $abs ]; then
            echo "$abs"
        fi
    done
}

# ls tmux session: tmux ls
# eg: tas main
function tas() {
    if [ $# != 1 ]; then
        echo "please assign one tmux session name"
        return
    fi
    local sname=$1
    local ret=$(tmux ls | grep "^$sname: ")
    if [ "$ret" = "" ]; then
        echo "can't find session: $sname"
        return
    fi
    local attached=$(echo $ret | grep "attached")
    if [ "$attached" != "" ]; then
        tmux detach-client -s $sname
    fi
    tmux attach -t $sname
}

function __check_is_common_file() {
    local file=$1
    if [ ! -e $file ]; then
        echo "$file does not exist"
        return 1
    fi
    if [ ! -f $file ]; then
        echo "$file is not a common file"
        return 1
    fi
    return 0
}

function tarfile() {
    if [ $# != 1 ]; then
        echo "usage: tarfile <file.tar.gz>"
        return
    fi
    local file=$1
    if ! __check_is_common_file $file; then
        return
    fi
    tar -tf $file | awk -F '/' '{print$1}' | sort -u
}

function unzipfile() {
    if [ $# != 1 ]; then
        echo "usage: unzipfile <file.zip>"
        return
    fi
    local file=$1
    if ! __check_is_common_file $file; then
        return
    fi
    unzip -l $file | sed '1,3d' | awk '{print$4}' | awk -F '/' '{print$1}' | sed '/^\s*$/d' | sort -u
}

function show_path_bash() {
    local pathes=(${PATH//:/ })

    for p in ${pathes[@]}; do
        echo "$p"
    done
}

function show_path_zsh() {
    local pathes=("${(@s/:/)PATH}")

    for p in ${pathes[@]}; do
        echo "$p"
    done
}

function showpath() {
    if is_bash; then
        show_path_bash
    elif is_zsh; then
        show_path_zsh
    else
        echo "It is currently neither bash nor zsh"
    fi
}
