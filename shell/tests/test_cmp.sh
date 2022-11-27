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

# 判断变量是否为空
para01=
if [ ! -n "$para01" ]; then
    echo "para01 is NULL"
fi
para01="xx"
if [ -n "$para01" ]; then
    echo "para01 is not NULL: $para01"
fi

# 判断变量是否为空
para02=
if [ ! $para02 ]; then
    echo "para02 is NULL"
fi
para02="yy"
if [ $para02 ]; then
    echo "para02 is not NULL: $para02"
fi

# 判断变量是否为空
para03=
if test -z $para03; then
    echo "para03 is NULL"
fi
para03="zz"
if ! test -z $para03; then
    echo "para03 is not NULL: $para03"
fi

# 判断变量是否为空
para04=
if [ "$para04" = "" ]; then
    echo "para04 is NULL"
fi
para04="aa"
if [ "$para04" != "" ]; then
    echo "para04 is not NULL: $para04"
fi
