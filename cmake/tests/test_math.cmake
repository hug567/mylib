# learning cmake math
# run: cmake -P test_math.cmake
# 2023.05.16

function(test_)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
endfunction()

function(main)
    test_()
endfunction()

main()
