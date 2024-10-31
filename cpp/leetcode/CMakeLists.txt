# compile cpp test files
# run: cmake .../cpp/leetcode; make
# 2023.05.22

cmake_minimum_required(VERSION 3.10.2)

project(cpp_tests CXX)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

set(CMAKE_CXX_COMPILER g++)
add_compile_options(-std=c++11 -Wall)

function(compile_single_file)
    foreach(file ${ARGV})
        # cmake --log-level=DEBUG
        get_filename_component(file_bin ${file} NAME_WE ABSOLUTE)
        message("will compile ${file} to ${file_bin}")
        add_executable(${file_bin} ${file})
    endforeach()
endfunction(compile_single_file)

file(GLOB cpp_files ./*.cpp)
file(GLOB cc_files ./*.cc)
set(source_files)
list(APPEND source_files ${cpp_files})
list(APPEND source_files ${cc_files})
compile_single_file(${source_files})
