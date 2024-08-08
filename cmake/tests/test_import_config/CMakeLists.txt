# 将autoconf.h中的配置引入到cmake中
# 运行：mkdir build; cmake ../
# 2024-08-07

cmake_minimum_required(VERSION 3.27)

project(test_import_config)

if(${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    message(FATAL_ERROR "Connot compile in source code dir")
endif()

#------------------------------------------------------------------------------#
function (parse_one_line line gfname)
    set(mstr)
    string(REGEX MATCH "^#" mstr ${line})
    if(NOT "x${mstr}" STREQUAL "x")
        message("will ignore defconfig line: [${line}]")
        return()
    endif()
    string(REPLACE "=" ";" line_list ${line})
    list(GET line_list 0 config_name)
    list(GET line_list 1 config_value)
    if("x${config_value}" STREQUAL "xy" OR "x${config_value}" STREQUAL "xm")
        set(config_value 1)
    endif()
    set(c_define "#define ${config_name} ${config_value}\n")
    message("will write to autoconf file: ${c_define}")
    file(APPEND ${gfname} ${c_define})
endfunction()

function(import_autoconf fname gfname)
    file(STRINGS ${fname} lines)
    foreach(line ${lines})
        parse_one_line(${line} ${gfname})
    endforeach()
endfunction()

function(ifdef config ret)
    set(autoconf ${PROJECT_BINARY_DIR}/autoconf.h)
    file(STRINGS ${fname} lines)
    foreach(line ${lines})
        string(REGEX MATCH "${config}" mstr ${line})
        if(NOT "x${mstr}" STREQUAL "x")
            set(${ret} TRUE PARENT_SCOPE)
            return()
        endif()
    endforeach()
    set(${ret} FALSE PARENT_SCOPE)
endfunction()
#------------------------------------------------------------------------------#

function(test_import_autoconf)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # 变量在autoconf.h中存在
    set(ret)
    set(config "CONFIG_NUMBER_01")
    ifdef(${config} ret)
    if(ret)
        message("var ${config} is defined in autoconf.h")
    else()
        message("var ${config} is not defined in autoconf.h")
    endif()

    # 变量在autoconf.h中不存在
    set(config "CONFIG_NUMBER_02")
    ifdef(${config} ret)
    if(NOT ret)
        message("var ${config} is not defined in autoconf.h")
    else()
        message("var ${config} is defined in autoconf.h")
    endif()
endfunction()

function(main)
    message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
    message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
    message("PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")

    #--------------------------------------------------------------------------#
    set(fname ${CMAKE_CURRENT_SOURCE_DIR}/defconfig)
    set(gfname ${PROJECT_BINARY_DIR}/autoconf.h)
    import_autoconf(${fname} ${gfname})
    #--------------------------------------------------------------------------#

    test_import_autoconf()
endfunction()

main()
