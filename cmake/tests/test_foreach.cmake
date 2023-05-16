# learning cmake foreach loop
# run: cmake -P test_foreach.cmake
# 2023.05.16

function(test_foreach)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # use foreach to traverse
    set(names Bob Tom Alice)
    foreach(name ${names})
        message("name: ${name}")
    endforeach()
endfunction()

function(test_foreach_range)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # traverse 0 to 5, the default step is 1
    foreach(var RANGE 0 5)
        message("var: ${var}")
    endforeach()

    # set step to 2
    foreach(var RANGE 0 10 2)
        message("var: ${var}")
    endforeach()
endfunction()

function(test_foreach_in)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # iterate over the elements in the list
    message("iterate over one list: -----")
    set(list 13 24 35 46)
    foreach(age IN LISTS list)
        message("age: ${age}")
    endforeach()

    # iterate over multiple lists
    message("iterate over multiple lists: -----")
    set(num01 1 3 5)
    set(num02 2 4 6)
    foreach(num IN LISTS num01 num02)
        message("num: ${num}")
    endforeach()

    # iterate over as items
    message("iterate over as items: -----")
    foreach(num IN ITEMS ${num01} ${num02})
        message("num: ${num}")
    endforeach()
endfunction()

function(test_foreach_break)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
    foreach(var RANGE 0 5)
        message("var: ${var}")
        if(${var} EQUAL 3)
            message("will break current loop, var: ${var}")
            break()
        endif()
    endforeach()
endfunction()

function(test_foreach_continue)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
    foreach(var RANGE 0 5)
        if(${var} EQUAL 3)
            message("will skip current loop by continue, var: ${var}")
            continue()
        endif()
        message("var: ${var}")
    endforeach()
endfunction()

function(main)
    test_foreach()
    test_foreach_range()
    test_foreach_in()
    test_foreach_break()
    test_foreach_continue()
endfunction()

main()
