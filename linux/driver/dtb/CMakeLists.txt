# learning linux dyb
# 2023-06-22

cmake_minimum_required(VERSION 3.10.2)

project(linux_dtb)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

add_executable(linux_dtb
    main.c
)
