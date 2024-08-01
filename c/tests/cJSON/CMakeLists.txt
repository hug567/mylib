# test cJSON lib
# 2024-08-01

cmake_minimum_required(VERSION 3.10.2)

project(tests_cJOSN)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

add_executable(test_int8
    test_int8.c
    cJSON.c
)
