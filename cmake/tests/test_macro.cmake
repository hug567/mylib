# learning cmake macro
# run: cmake -P test_macro.cmake
# 2023.05.16

# macro without parameter and return value
macro(test_print)
    message("test_print: --------------------------------------")
    message("hello cmake macro")
endmacro()

# macro with parameter
macro(test_with_param name age)
    message("test_with_param: ---------------------------------")
    message("ARGC: ${ARGC}")
    message("name: ${name}, age: ${age}")
endmacro()

# macro with multiple parameters
macro(test_multi_param)
    message("test_multi_param: --------------------------------")
    message("ARGC: ${ARGC}")
    message("ARGV: ${ARGV}")
    message("ARGN: ${ARGN}")
    set(i 0)
    foreach(var ${ARGV})
        message("ARGV${i}: ${var}")
        math(EXPR i "${i} + 1")
    endforeach()
endmacro()

# log function implemented using macro
# it is better to use in a cmake function
macro(test_log)
    message("[${CMAKE_CURRENT_FUNCTION}:${CMAKE_CURRENT_FUNCTION_LIST_LINE}] ${ARGV}")
endmacro()

# log function implemented using macro
# it prints the line number in the macro, which is not recommended
macro(test_log2)
    message("[${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}] ${ARGV}")
endmacro()

function(main)
    # call function
    test_print()
    # call function with parameter
    test_with_param("Bob" 18)
    # call function with multiple parameters
    test_multi_param(1 2 3 4 5)
    # log macro
    set(name "Tom")
    test_log("My name is ${name}")
endfunction()

main()

test_log("test_log: This log is not in a function")
test_log2("test_log2: This log is not in a function")
message("[${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}] message: This log is not in a function")
