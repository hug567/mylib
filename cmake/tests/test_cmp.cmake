# learning cmake compare
# run: cmake -P test_cmp.cmake
# 2023.05.16

function(test_cmp_number)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(num01 5)
    set(num02 5)
    if(${num01} EQUAL ${num02})
        message("${num01} == ${num02}")
    endif()

    set(num01 6)
    set(num02 5)
    if(${num01} GREATER ${num02})
        message("${num01} > ${num02}")
    endif()

    set(num01 4)
    set(num02 5)
    if(${num01} LESS ${num02})
        message("${num01} < ${num02}")
    endif()

    set(num01 6)
    set(num02 5)
    if(${num01} GREATER_EQUAL ${num02})
        message("${num01} >= ${num02}")
    endif()

    set(num01 5)
    set(num02 5)
    if(${num01} LESS_EQUAL ${num02})
        message("${num01} <= ${num02}")
    endif()
endfunction()

function(test_cmp_string)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(str01 "abc")
    set(str02 "abc")
    if(${str01} STREQUAL ${str02})
        message("${str01} == ${str02}")
    endif()

    set(str01 "abc")
    set(str02 "ABC")
    if(${str01} STRGREATER ${str02})
        message("${str01} > ${str02}")
    endif()

    set(str01 "abc")
    set(str02 "def")
    if(${str01} STRLESS ${str02})
        message("${str01} < ${str02}")
    endif()

    set(str01 "abc")
    set(str02 "ABC")
    if(${str01} STRGREATER_EQUAL ${str02})
        message("${str01} >= ${str02}")
    endif()

    set(str01 "abc")
    set(str02 "abc")
    if(${str01} STRLESS_EQUAL ${str02})
        message("${str01} <= ${str02}")
    endif()
endfunction()

function(main)
    test_cmp_number()
    test_cmp_string()
endfunction()

main()
