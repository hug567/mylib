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

function(main)
    test_if()
endfunction()

main()
