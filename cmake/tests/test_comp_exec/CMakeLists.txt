# learning cmake compile exectuable
# run: cmake .../camke/tests/test_comp_exec; make VERBOSE=1
# 2023.05.16

cmake_minimum_required(VERSION 3.10.2)

project(test_comp_exec)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

# add compile options, effective for all source files
# include the specified header file in the form of compile options
add_compile_options(-include${CMAKE_CURRENT_SOURCE_DIR}/../src/include/info.h)

add_executable(hello.elf
    ../src/hello.c
)

# include the specified header file in the form of compile options
# only applies to the current target
target_compile_options(hello.elf PRIVATE
    -include ${CMAKE_CURRENT_SOURCE_DIR}/../src/include/price.h)
