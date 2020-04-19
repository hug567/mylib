# cmake最低版本要求
cmake_minimum_required(VERSION 2.6)

# cmake工程名称
project(cmake_practice)

# 添加搜索.cmake路径
# 包含cmake脚本
include(./script/common.cmake)
mt_log("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
mt_info("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
mt_error("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
mt_var(CMAKE_CURRENT_SOURCE_DIR)
set(tmp_var ${CMAKE_CURRENT_SOURCE_DIR})
mt_var(tmp_var)

mt_file("test function mt_file")
mt_file_var(CMAKE_CURRENT_SOURCE_DIR)
mt_file_var(CMAKE_CURRENT_SOURCE_DIR_XXX)

#消息提示
message("[INFO]: start compile project")
# 工程源码路径
message("[INFO]: CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
# 当前源码路径
message("[INFO]: CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
#
message("[INFO]: CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")

# 编译可执行文件
add_executable(hello.elf
	main.c
	)

# 生成动态库
add_library(test SHARED
	test_so.c
	)
# 为动态库添加版本号
SET_TARGET_PROPERTIES(test PROPERTIES VERSION 0.1 SOVERSION 1)

# 添加搜索.cmake路径
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
# 包含cmake脚本
#include(./include.cmake) # 相对路径
include(include)
