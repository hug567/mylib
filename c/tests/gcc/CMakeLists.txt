# 测试带头节点的循环双链表
# 2024-08-20

cmake_minimum_required(VERSION 3.10.2)

project(gcc_test)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

add_executable(test_macro
    test_macro.c
)
