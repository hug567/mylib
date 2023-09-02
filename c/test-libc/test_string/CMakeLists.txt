cmake_minimum_required(VERSION 3.5)

project(test_string)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

add_executable(test_str_arr
    test_str_arr.c
)
