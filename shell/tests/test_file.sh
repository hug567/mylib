#!/bin/bash

# 逐行读取文件
function read_file_by_line() {
    echo "$FUNCNAME:-----------------------------"

    local file=$1
    # 方式一
    while read line
    do
        echo "${line}"
    done < $file

    # 方式二
    cat $file | while read line
    do
        echo "${line}"
    done
}

# -e 判断对象是否存在
# -d 判断对象是否存在，并且为目录
# -f 判断对象是否存在，并且为常规文件
# -L 判断对象是否存在，并且为符号链接
# -h 判断对象是否存在，并且为软链接
# -s 判断对象是否存在，并且长度不为0
# -r 判断对象是否存在，并且可读
# -w 判断对象是否存在，并且可写
# -x 判断对象是否存在，并且可执行
# -O 判断对象是否存在，并且属于当前用户
# -G 判断对象是否存在，并且属于当前用户组
# -nt 判断file1是否比file2新  [ "/data/file1" -nt "/data/file2" ]
# -ot 判断file1是否比file2旧  [ "/data/file1" -ot "/data/file2" ]
function test_file_exist() {
    echo "$FUNCNAME:-----------------------------"
    local file

    file=/tmp
    if [ ! -e $file ]; then
        echo "$file does not exist"
    fi
    file=/tmp/vim_tmp.txt
    if [ ! -e $file ]; then
        echo "$file does not exist"
    fi
}

# 从文件路径中获取各个部分
function test_get_fname() {
    echo "$FUNCNAME:-----------------------------"

    local fname="modemserver.log-20240927-074847.gz"
    local base1=${fname%.*} # modemserver.log-20240927-074847
    echo "base1: ${base1}"
    local base2=${fname%%.*} # modemserver
    echo "base2: ${base2}"
}

function main() {
    read_file_by_line /tmp/vim_tmp.txt
    test_file_exist
    test_get_fname
}

main
