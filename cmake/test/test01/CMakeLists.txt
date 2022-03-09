# 测试：同时使用add_compile_options和target_compile_options添加-include头文件
# cmake版本：3.10.2
# 结论：同时使用add_compile_options和target_compile_options添加-include头文件，
#       头文件路径为绝对路径，则两个-include后不能都有空格，否则编译报错，可以
#       一个-include后有空格，另一个没有，或者两个后面都没有空格
# 2022-03-09

# cmake最低版本要求
cmake_minimum_required(VERSION 3.10.2)

# cmake工程名称
project(test01)

# 编译可执行文件
add_executable(test01.elf
    main.c
)
add_compile_options(-include${CMAKE_CURRENT_SOURCE_DIR}/a.h)
target_compile_options(test01.elf PRIVATE -include ${CMAKE_CURRENT_SOURCE_DIR}/b.h)
