# learning c syntax
# 2023-06-15

cmake_minimum_required(VERSION 3.10.2)

project(tests_c)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

function(compile_single_file)
    foreach(file ${ARGV})
        # cmake --log-level=DEBUG
        message(DEBUG "[${CMAKE_CURRENT_FUNCTION}] file: ${file}")
        string(REGEX MATCH "[A-Za-z0-9_-]+\.c$" file_bin ${file})
        string(REGEX MATCH "^[A-Za-z0-9_-]+" file_bin ${file_bin})
        message(DEBUG "[${CMAKE_CURRENT_FUNCTION}] file_bin: ${file_bin}")
        add_executable(${file_bin} ${file})
    endforeach()
endfunction(compile_single_file)

file(GLOB test_files *.c)
compile_single_file(${test_files})

add_subdirectory(attribute)
