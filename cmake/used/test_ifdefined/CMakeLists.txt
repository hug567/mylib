# cmake判断autoconf.h中是否定义了指定宏
# 运行: cmake .../test_ifdefined/CMakeLists.txt
# 2024-10-16

cmake_minimum_required(VERSION 3.10.2)

project(test_ifdefined)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

#------------------------------------------------------------------------------#
set(autoconf ${CMAKE_CURRENT_SOURCE_DIR}/autoconf.h)

# eg: ifdefined(ret CONFIG_XX)
function(ifdefined ret config)
    file(STRINGS ${autoconf} lines)
    foreach(line ${lines})
        string(REGEX MATCH "${config}" mstr ${line})
        if(NOT "x${mstr}" STREQUAL "x")
            set(${ret} TRUE PARENT_SCOPE)
            return()
        endif()
    endforeach()
    set(${ret} FALSE PARENT_SCOPE)
endfunction()

# eg: ifdefined_or(ret CONFIG_XX [CONFIG_YY] [...])
function(ifdefined_or ret_or)
    set(ret)
    foreach(config IN LISTS ARGN)
        ifdefined(ret ${config})
        if(ret)
            set(${ret_or} TRUE PARENT_SCOPE)
            return()
        endif()
    endforeach()
    set(${ret_or} FALSE PARENT_SCOPE)
endfunction()

# eg: ifdefined_and(ret CONFIG_XX [CONFIG_YY] [...])
function(ifdefined_and ret_and)
    set(ret)
    foreach(config IN LISTS ARGN)
        ifdefined(ret ${config})
        if(NOT ret)
            set(${ret_and} FALSE PARENT_SCOPE)
            return()
        endif()
    endforeach()
    set(${ret_and} TRUE PARENT_SCOPE)
endfunction()
#------------------------------------------------------------------------------#

function(test_ifdefined)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # 判断单个宏是否已定义
    set(ret)
    ifdefined(ret CONFIG_TEST_INT)
    if(ret)
        message("CONFIG_TEST_INT is defined")
    endif()

    # 与：判断两个宏必须都定义
    set(ret2)
    set(ret3)
    ifdefined(ret2 CONFIG_TEST_INT)
    ifdefined(ret3 CONFIG_TEST_STRING)
    if(ret2 AND ret3)
        message("CONFIG_TEST_INT and CONFIG_TEST_STRING is defined")
    endif()

    # 或：判断两个宏中至少有一个已定义
    set(ret4)
    set(ret5)
    ifdefined(ret4 CONFIG_TEST_INT)
    ifdefined(ret5 CONFIG_TEST_XXX)
    if(ret2 OR ret3)
        message("CONFIG_TEST_INT or CONFIG_TEST_XXX is defined")
    endif()
endfunction()

# 或：判断多个宏中至少有一个已定义
function(test_ifdefined_or)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(ret)
    # 至少有一个定义(写在多行)
    ifdefined_or(ret CONFIG_TEST_INT CONFIG_TEST_STRING
                     CONFIG_TEST_XXX CONFIG_TEST_YYY)
    if(ret)
        message("CONFIG_TEST_INT or CONFIG_TEST_STRING or CONFIG_TEST_XXX or CONFIG_TEST_YYY is defined")
    endif()

    # 都没有定义
    ifdefined_or(ret CONFIG_TEST_XXX CONFIG_TEST_YYY)
    if(ret)
        message("CONFIG_TEST_XXX or CONFIG_TEST_YYY is defined")
    else()
        message("CONFIG_TEST_XXX and CONFIG_TEST_YYY is all not defined")
    endif()
endfunction()

# 与：判断多个宏中至少有一个已定义
function(test_ifdefined_and)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(ret)
    # 多个宏均定义
    ifdefined_and(ret CONFIG_TEST_INT CONFIG_TEST_STRING)
    if(ret)
        message("CONFIG_TEST_INT and CONFIG_TEST_STRING is all defined")
    endif()

    # 至少有一个没有定义
    ifdefined_and(ret CONFIG_TEST_INT CONFIG_TEST_YYY)
    if(ret)
        message("CONFIG_TEST_INT and CONFIG_TEST_YYY is all defined")
    else()
        message("CONFIG_TEST_INT and CONFIG_TEST_YYY at least one is not defined")
    endif()
endfunction()

function(main)
    message("${CMAKE_CURRENT_FUNCTION}: ---------------------------------start")
    test_ifdefined()
    test_ifdefined_or()
    test_ifdefined_and()
    message("${CMAKE_CURRENT_FUNCTION}: -----------------------------------end")
endfunction()

main()
