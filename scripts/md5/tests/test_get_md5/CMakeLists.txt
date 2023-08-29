cmake_minimum_required(VERSION 3.10.2)

project(test_get_md5)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

add_executable(test_get_md5
    test_get_md5.c
    ../lib/md5.c
)
