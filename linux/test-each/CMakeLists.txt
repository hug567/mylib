cmake_minimum_required(VERSION 3.10.2)
project(test-each)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "Do not compile in the source directory")
endif()

# 使用说明
function(usage)
    message("Usage:")
    message("  cmake -DARCH=host     make host machine test file")
    message("  cmake -DARCH=arm      make arm plat test file")
    message("  cmake -DARCH=arm64    make arm64 plat test file")
endfunction(usage)

function(compile_single_file)
    set(i 0)
    while(i LESS ${ARGC})
        set(test_file ${ARGV${i}})
        string(REGEX MATCH "[A-Za-z0-9_]+\.c$" test_file ${test_file})
        string(REGEX MATCH "^[A-Za-z0-9_]+" test_file_bin ${test_file})
        message("After make, will compile [${test_file}] to [${test_file_bin}]")
        add_executable(${test_file_bin} ${test_file})
        math(EXPR i "${i} + 1")
    endwhile()
endfunction(compile_single_file)

set(MYLIB $ENV{MYLIB} CACHE STRING "mylib")
#include(${MYLIB}/cmake/script/common.cmake)

if(NOT ARCH)
    usage()
    message(FATAL_ERROR "Does not define ARCH")
endif()

if(${ARCH} STREQUAL "host")
    set(CMAKE_C_COMPILER gcc)
elseif(${ARCH} STREQUAL "arm")
    set(CMAKE_C_COMPILER arm-linux-gnueabi-gcc)
elseif(${ARCH} STREQUAL "arm64")
    set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
else()
    usage()
    message(FATAL_ERROR "Does not support ARCH: ${ARCH}")
endif()

#log_info("CMAKE_C_COMPILER = ${CMAKE_C_COMPILER}")

# 编译单个文件的测试用例
compile_single_file(
    test_get_time.c
    test_proc_ioctl.c
)
