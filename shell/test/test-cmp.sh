#!/bin/bash

# 脚本参数个数
echo $#

# 当前目录
cur_dir=$(pwd)
echo "cur_dir = ${cur_dir}"
# 判断目录存在
if [ -d ${cur_dir} ]; then
	echo "${cur_dir} does exist"
fi
# 判断目录不存在
if [ ! -d ${cur_dir} ]; then
	echo "${cur_dir} does not exist"
fi
