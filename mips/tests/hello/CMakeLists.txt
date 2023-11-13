cmake_minimum_required(VERSION 3.10.2)
project(test_hello)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "Do not compile in the source directory")
endif()

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR mips)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(CMAKE_C_COMPILER /usr/bin/mipsel-linux-gnu-gcc)

add_definitions(-Wall -mips32r2 -march=interaptiv)

add_executable(hello.elf
    hello.c
)
