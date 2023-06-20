#!/bin/bash

function sync_clipboard() {
    local user=$1
    local ip=$2
    local new_md5=
    local old_md5=
    
    cd ~
    scp $user@$ip:/tmp/vim_tmp.txt . &> /dev/null
    if [ ! -f vim_tmp.txt ]; then
        return
    fi
    new_md5=$(md5sum vim_tmp.txt | awk '{print$1}')
    if [ -f vim_tmp-old.txt ]; then
        old_md5=$(md5sum vim_tmp-old.txt | awk '{print$1}')
    fi
    if [ "$new_md5" != "$old_md5" ]; then
        echo "Update windows clipboard"
        #echo "new_md5: $new_md5"
        #echo "old_md5: $old_md5"
        cat vim_tmp.txt | clip
    fi
    if [ -f vim_tmp-old.txt ]; then
        rm vim_tmp-old.txt
    fi
    mv vim_tmp.txt vim_tmp-old.txt
}

function main() {
    local i=0
    while true; do
        echo "loop: $i"
        sync_clipboard hx 10.110.192.42
        sleep 1
        let i=i+1
    done
}

main $*