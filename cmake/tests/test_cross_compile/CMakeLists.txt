# learning cmake cross compile
# run: cmake .../camke/tests/test_cross_compile; make VERBOSE=1
# 2023-06-28

cmake_minimum_required(VERSION 3.10.2)

project(test_cross_compile)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(TOOLCHAIN /home/hx/tools/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu)
set(CMAKE_C_COMPILER ${TOOLCHAIN}/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN}/bin/aarch64-linux-gnu-g++)

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
