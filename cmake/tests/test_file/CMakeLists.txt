# learning cmake add_custom_target/command
# run: cmake .../test_file/
# Create: 2024-09-26 17:28:33

cmake_minimum_required(VERSION 3.10.2)

project(test_file)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

message("[start]: ------------------------------------------------------------")

# 判断相对于当前源码目录的文件是否存在
set(fname "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt")
message("fname: ${fname}")
if(EXISTS ${fname})
    message("file ${fname} exists")
endif()

set(fname "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists2.txt")
message("fname: ${fname}")
if(NOT EXISTS ${fname})
    message("file ${fname} does not exist")
endif()

message("[end]: --------------------------------------------------------------")
