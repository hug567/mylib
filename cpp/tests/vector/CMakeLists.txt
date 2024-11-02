# compile cpp test files
# run: cmake .../cpp/tests/vector; make
# 2024-11-01

cmake_minimum_required(VERSION 3.10.2)

project(cpp_tests CXX)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

set(CMAKE_CXX_COMPILER g++)
add_compile_options(-std=c++11 -Wall -Werror)

function(compile_single_file)
    foreach(file ${ARGV})
        get_filename_component(file_bin ${file} NAME_WE ABSOLUTE)
        message("will compile ${file} to ${file_bin}")
        add_executable(${file_bin} ${file})
    endforeach()
endfunction(compile_single_file)

file(GLOB source_files ./*.cc)
compile_single_file(${source_files})
