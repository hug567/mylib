#!/usr/bin/zsh

cur_file=${0:a}
cur_dir=$(dirname $cur_file)
echo "cur_file: [$cur_file]"
echo "cur_dir: [$cur_dir]"

source $cur_dir/test03/test03.sh
