# learning cmake compile library
# run: cmake .../camke/tests/test_comp_lib
# 2023.05.16

cmake_minimum_required(VERSION 3.10.2)

project(test_comp_lib)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

add_library(math SHARED
    ../src/math.c
)
