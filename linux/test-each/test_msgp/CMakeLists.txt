cmake_minimum_required(VERSION 3.10.2)
project(test_msgp)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "Do not compile in the source directory")
endif()

add_executable(client
    client.c
)

add_executable(server
    server.c
)
