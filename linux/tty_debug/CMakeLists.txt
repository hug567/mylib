cmake_minimum_required(VERSION 3.10.2)
project(tty_debug)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
	message(FATAL_ERROR "Not allowed to compile in the source directory")
endif()

include(common.cmake)

log_info_var(CMAKE_CURRENT_SOURCE_DIR)
log_info_var(CMAKE_CURRENT_BINARY_DIR)
