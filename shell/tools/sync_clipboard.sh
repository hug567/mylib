#!/bin/bash

function sync_clipboard() {
    local user=$1
    local ip=$2
    local new_file="paste.txt"
    local old_file="paste-old.txt"
    local new_md5=
    local old_md5=

    cd ~
    scp $user@$ip:/tmp/vim/$new_file . &> /dev/null
    if [ ! -f $new_file ]; then
        return
    fi
    new_md5=$(md5sum $new_file | awk '{print$1}')
    if [ -f $old_file ]; then
        old_md5=$(md5sum old_file | awk '{print$1}')
    fi
    if [ "$new_md5" != "$old_md5" ]; then
        echo "Update windows clipboard"
        #echo "new_md5: $new_md5"
        #echo "old_md5: $old_md5"
        cat $new_file | clip
    fi
    if [ -f $old_file ]; then
        rm $old_file
    fi
    mv $new_file $old_file
}

function main() {
    local i=0
    while true; do
        if [ $(expr $i % 10) -eq 0 ]; then
            echo "loop: $i"
        fi
        sync_clipboard hx 10.110.192.42
        sleep 1
        let i=i+1
    done
}

main $*
