# learning cmake if
# run: cmake -P test_if.cmake
# 2023.05.16

function(test_if)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(var01 xx)
    if(DEFINED var01)
        message("var01 is defined")
    endif()

    set(var02)
    if(NOT DEFINED var02)
        message("var02 is not defined")
    endif()
endfunction()

function(test_if_else)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(num 5)
    if(${num} EQUAL 4)
        message("${num} == 4")
    else()
        message("${num} != 4")
    endif()
endfunction()

function(test_if_elseif)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(num 5)
    if(${num} EQUAL 4)
        message("${num} == 4")
    elseif(${num} EQUAL 5)
        message("${num} == 5")
    else()
        message("${num} != 4 and 5")
    endif()
endfunction()

function(test_if_basic)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
    # true: 1 ON TRUE'non-zero number'
    # false: 0 OFF FALSE IGNORE NOTFOUND x-NOTFOUND 'empty tring'
    set(var01 1)
    if(${var01})
        message("if condition is true: var01 = ${var01}")
    endif()
    # 判断字符串相等
    set(var02 Y)
    if("x${var02}" STREQUAL "xY")
        message("if condition is true: var02 = ${var02}")
    endif()
    # 判断字符串不等
    if(NOT "x${var02}" STREQUAL "xX")
        message("var01(${var01}) is not equal X")
    endif()

    if(DEFINED ENV{PATH})
        message("env var is defined: PATH")
    endif()
endfunction()

function(main)
    test_if()
    test_if_else()
    test_if_elseif()
    test_if_basic()
endfunction()

main()
