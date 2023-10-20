#!/bin/bash

function save_buffer() {
    local new_file="/tmp/vim/tmux_buffer.txt"
    local old_file="/tmp/vim/tmux_buffer-old.txt"
    local vim_tmp_dir="/tmp/vim"
    local vim_tmp_file="/tmp/vim/paste.txt"
    local new_md5=
    local old_md5=

    if [ ! -d $vim_tmp_dir ]; then
        return
    fi
    if [ ! -f $new_file ]; then
        touch $new_file
    fi
    tmux save-buffer $new_file
    local size=$(ls -l $new_file | awk '{print$5}')
    if [ $size -eq 0 -o $size -gt 10485760 ]; then
        rm $new_file
        return
    fi
    new_md5=$(md5sum $new_file | awk '{print$1}')
    if [ -f $old_file ]; then
        old_md5=$(md5sum $old_file | awk '{print$1}')
    fi
    if [ "$new_md5" != "$old_md5" ]; then
        #echo "will copy $new_file to $vim_tmp_file"
        rm $vim_tmp_file
        cp $new_file $vim_tmp_file
    fi
    if [ -f $old_file ]; then
        rm $old_file
    fi
    mv $new_file $old_file
}

function main() {
    local i=0
    local finish_file="/tmp/vim/tmux_finish.txt"

    if [ -f $finish_file ]; then
        rm $finish_file
    fi
    while true; do
        if [ -f $finish_file ]; then
            exit 0
        fi
        if [ $(expr $i % 10) -eq 0 ]; then
            echo "loop: $i" > /dev/null
        fi
        #echo "loop: $i"
        save_buffer
        sleep 1
        let i=i+1
    done
}

main $*
