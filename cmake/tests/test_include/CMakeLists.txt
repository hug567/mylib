# learning include cmake script
# run: cmake .../test_include
# 2023-05-22

cmake_minimum_required(VERSION 3.10.2)

project(test_include)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

# include cmake script files with relative or absolute paths
include(./common.cmake)
print_info(Bob 18)

# add cmake script search path to system var: CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# will search cmake script in CMAKE_MODULE_PATH, the extension .cmake can be omitted
include(math)
add(3 5 sum)
message("3 + 5 = ${sum}")
