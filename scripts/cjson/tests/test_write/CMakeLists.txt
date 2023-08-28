cmake_minimum_required(VERSION 3.10.2)

project(test_write)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src)

add_executable(test_write
    test_write.c
    ../../src/cJSON.c
)
