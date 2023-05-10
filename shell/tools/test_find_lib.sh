#!/bin/bash

CROSS_COMPILE=arm-none-linux-gnueabi-
gcc_path=$(which ${CROSS_COMPILE}gcc)
gcc_dir=$(dirname ${gcc_path})
compiler_dir=$(cd ${gcc_dir}/..; pwd)
compiler_lib="${compiler_dir}/arm-none-linux-gnueabi/libc/usr"
compiler_libs_dir="${compiler_lib}/lib"
compiler_headers_dir="${compiler_lib}/include"

echo "gcc_path = ${gcc_path}"
echo "gcc_dir = ${gcc_dir}"
echo "compiler_dir = ${compiler_dir}"
echo "compiler_lib = ${compiler_lib}"
echo "compiler_libs_dir = ${compiler_libs_dir}"
echo "compiler_headers_dir = ${compiler_headers_dir}"

echo ""
ls ${compiler_libs_dir}
echo ""
ls ${compiler_headers_dir}
