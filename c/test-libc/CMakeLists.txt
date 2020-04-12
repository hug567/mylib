# cmake最低版本要求
cmake_minimum_required(VERSION 2.6)

# cmake工程名称
project(test_libc)

message("CMAKE_C_COMPILER = ${CMAKE_C_COMPILER}")

# 编译可执行文件
add_executable(a.elf
    main.c
    )
