# learning cmake add_custom_target/command
# run: cmake .../test_custom
# 2023-05-23

cmake_minimum_required(VERSION 3.10.2)

project(test_custom)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

# after cmake, run: make test01
add_custom_target(test01
    COMMAND echo "this is custom target test01"
)

# add command for target
add_custom_command(TARGET test01
    COMMAND echo "this is a log print by add_custom_command"
)
