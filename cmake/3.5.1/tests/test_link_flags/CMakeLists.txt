# test set link flags with cmake 3.5.1 (ubuntu 16.04)
# run: cmake .../test_link_flags
#      make VERBOSE=1
# 2023-08-16

cmake_minimum_required(VERSION 3.5.1)

project(test_link_flags)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

add_executable(test_link_flags
    main.c
)
# set link flags
set_target_properties(test_link_flags
    PROPERTIES
    LINK_FLAGS "-lc"
)
