# learning cmake function
# run: cmake -P test_function.cmake
# 2023.05.16

# function without parameter and return value
function(test_print)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
    message("hello cmake")
    message("CMAKE_CURRENT_FUNCTION_LIST_DIR = ${CMAKE_CURRENT_FUNCTION_LIST_DIR}")
    message("CMAKE_CURRENT_FUNCTION_LIST_FILE = ${CMAKE_CURRENT_FUNCTION_LIST_FILE}")
    message("CMAKE_CURRENT_FUNCTION = ${CMAKE_CURRENT_FUNCTION}")
    message("CMAKE_CURRENT_FUNCTION_LIST_LINE = ${CMAKE_CURRENT_FUNCTION_LIST_LINE}")
endfunction()

# function with parameter
function(test_with_param name age)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
    message("ARGC: ${ARGC}")
    message("name: ${name}, age: ${age}")
endfunction()

# function with multiple parameters
function(test_multi_param)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
    message("ARGC: ${ARGC}")
    message("ARGV: ${ARGV}")
    message("ARGN: ${ARGN}")
    set(i 0)
    foreach(var ${ARGV})
        message("ARGV${i}: ${var}")
        math(EXPR i "${i} + 1")
    endforeach()
endfunction()

# save return value in parameter
function(test_func_return retval)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
    set(${retval} "this is a return value" PARENT_SCOPE)
endfunction()

function(main)
    # call function
    test_print()
    # call function with parameter
    test_with_param("Bob" 18)
    # call function with multiple parameters
    test_multi_param(1 2 3 4 5)

    # function return value
    set(ret)
    test_func_return(ret)
    message("ret: ${ret}")
endfunction()

main()
