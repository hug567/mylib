# cmake最低版本要求
cmake_minimum_required(VERSION 2.6)

# cmake工程名称
project(cmake_practice)

#消息提示
message("[INFO]: start compile project")
message("[INFO]: CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message("[INFO]: CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message("[INFO]: CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")

# 编译可执行文件
add_executable(hello.elf
	main.c
	)

# 添加搜索.cmake路径
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
# 包含cmake脚本
#include(./include.cmake) # 相对路径
include(include)
