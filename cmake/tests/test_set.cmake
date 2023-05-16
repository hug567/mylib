# learning cmake set variable
# run: cmake -P test_set.cmake
# 2023.05.16

function(test_)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
endfunction()

function(main)
    test_()
endfunction()

main()
