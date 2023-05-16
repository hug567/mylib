# learning cmake compile exectuable
# run: cmake .../camke/tests/test_comp_exec
# 2023.05.16

cmake_minimum_required(VERSION 3.10.2)

project(test_comp_exec)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

add_executable(hello.elf
    ../src/hello.c
)
