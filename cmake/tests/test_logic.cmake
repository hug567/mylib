# learning cmake logic
# run: cmake -P test_logic.cmake
# 2023.05.16

# AND OR NOT

# AND OR NOT
function(test_logic)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
    set(num1 1)
    set(num2 2)
    if(${num1} EQUAL 1 AND ${num2} EQUAL 2)
        message("num1 == 1 and num2 == 2")
    endif()

    if(${num1} EQUAL 3 OR ${num2} EQUAL 2)
        message("num1 == 3 or num2 == 2")
    endif()

    if(NOT EXISTS /tmp/cmakexx)
        message("file or dir /tmp/cmakexx does not exist")
    endif()
endfunction()

function(main)
    test_logic()
endfunction()

main()
