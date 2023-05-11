#!/bin/bash

function getdir(){
    for element in `ls $1`
    do
        dir_or_file=$1"/"$element
        if [ -d $dir_or_file ]
        then
            chmod 755 $dir_or_file
            getdir $dir_or_file
        else
            #echo $dir_or_file
            chmod 644 $dir_or_file
        fi
    done
}
root_dir=`pwd`
getdir $root_dir
