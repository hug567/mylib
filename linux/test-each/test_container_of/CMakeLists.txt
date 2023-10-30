cmake_minimum_required(VERSION 3.10.2)
project(test_msgp)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "Do not compile in the source directory")
endif()

add_definitions(-Wall)

add_executable(test_container_of
    test_container_of.c
)
