cmake_minimum_required (VERSION 3.10.2)

project(TEST01)

set(TEST_WRAP test01.elf)

set(SRC main.c test01.c)

#add_compile_options(-Wl,--wrap=test01_print)
#add_compile_options("-Wl,--wrap=test01_print")
#add_definitions(-Wl,--wrap=test01_print)
#add_definitions("-Wl,--wrap=test01_print")

#set(CMAKE_C_FLAGS "-Wl,--wrap=test01_print")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap=test01_print")

add_executable(${TEST_WRAP} ${SRC})

#target_compile_definitions(${TEST_WRAP}
#	PRIVATE
#	-Wl,--wrap=test01_print
#	)
