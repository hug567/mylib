# compile cpp test files
# run: cmake .../cpp/tests; make
# 2023.05.22

cmake_minimum_required(VERSION 3.10.2)

project(cpp_tests CXX)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

set(CMAKE_CXX_COMPILER g++)
add_compile_options(-std=c++11 -Wall -Werror)

function(compile_single_file)
    foreach(file ${ARGV})
        message(DEBUG "[${CMAKE_CURRENT_FUNCTION}] file: ${file}")
        string(REGEX MATCH "[A-Za-z0-9_-]+\.c.*$" file_bin ${file})
        string(REGEX MATCH "^[A-Za-z0-9_-]+" file_bin ${file_bin})
        add_executable(${file_bin} ${file})
    endforeach()
endfunction(compile_single_file)

compile_single_file(
    test_sort.cpp
    test_string.cpp
    test_function.cpp
    test_vector.cc
)
