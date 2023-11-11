cmake_minimum_required(VERSION 3.10.2)
project(test_hello)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "Do not compile in the source directory")
endif()

SET(CMAKE_SYSTEM_NAME Linux)     # this one is important
#SET(CMAKE_SYSTEM_VERSION 1)      # this one not so much
SET(CMAKE_SYSTEM_PROCESSOR mips)

add_definitions(-Wall)

add_executable(hello.elf
    hello.c
)
