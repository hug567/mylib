cmake_minimum_required(VERSION 3.10.2)
project(test-each)

set(MYLIB $ENV{MYLIB} CACHE STRING "mylib")
include(${MYLIB}/cmake/script/common.cmake)
#log_info("[${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}] MYLIB = ${MYLIB}")

function(compile_single_file files)
    log_info_var(ARGC)
    log_info_var(ARGN)
    log_info_var(files)
endfunction(compile_single_file)


string(REGEX MATCH "([a-z_]+)\.c$" TEST_FILE mylib/linuxux/test_get_time.c)
string(REGEX MATCH "(^[a-z_]+)" TEST_FILE_BIN ${TEST_FILE})
log_info_var(TEST_FILE)
log_info_var(TEST_FILE_BIN)

add_executable(test_get_time
    test_get_time.c
)

set(single_test_file)

compile_single_file(
    test01.c
    test02.c
    test03.c
    test04.c
    test05.c
)
