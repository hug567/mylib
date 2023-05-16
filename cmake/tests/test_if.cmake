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

function(main)
    test_if()
    test_if_else()
    test_if_elseif()
endfunction()

main()
