# learning cmake message function
# run: cmake -P test_message.cmake
# 2023.05.16

function(test_generage_message)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # print string
    message("this is a common string")

    # print variable
    message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

    message(TRACE "this is a trace message") # cmake --log-level=TRACE
    message(DEBUG "this is a debug message") # cmake --log-level=DEBUG
    message(VERBOSE "this is a verbose message") # cmake --log-level=VERBOSE
    message(STATUS "this is a status message")
    message(NOTICE "this is a notice message") # default log level
    # with DEPRECATION, cmake execution will continue
    message(DEPRECATION "this is a deprecation message")
    # with AUTHOR_WARNING, cmake execution will continue
    message(AUTHOR_WARNING "this is an author warning message")
    # with WARNING, cmake execution will continue
    message(WARNING "this is a warning message")
    # with SEND_ERROR, cmake execution will continue
    message(SEND_ERROR "this is a send error message")
    # with FATAL_ERROR, cmake execution is aborted
    #message(FATAL_ERROR "this is a fatal error message")
endfunction()

function(test_reporting_check)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    message(CHECK_START "start")
    message(CHECK_PASS "pass")
    message(CHECK_START "start")
    message(CHECK_FAIL "fail")
endfunction()

function(main)
    test_generage_message()
    test_reporting_check()
endfunction()

main()
