cmake_minimum_required(VERSION 3.16)
project(leetcode C)

set(CMAKE_C_STANDARD 99)

add_executable(leetcode common.h leetcode_0208.c)
target_compile_options(leetcode PRIVATE -Wall)