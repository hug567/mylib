# learning cmake set variable
# run: cmake -P test_set.cmake
# 2023.05.16

function(test_normal)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(num 123)
    message("num = ${num}")
    set(num 456)
    message("num = ${num}")

    set(str "hello cmake")
    message("str = ${str}")
endfunction()

# global variable
function(test_cache_entry)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # bool
    set(ENABLED ON CACHE BOOL "config is enabled")
    if(ENABLED) # bool var in if
        message("ENABLED: ${ENABLED}")
    endif()
    set(DISABLED OFF CACHE BOOL "config is disabled")
    if(NOT DISABLED)
        message("DISABLED: ${DISABLED}")
    endif()

    # filepath
    set(file /tmp/vim_tmp.txt CACHE FILEPATH "vim tmp file")
    message("file: ${file}")

    # path
    set(dir /tmp/cmake CACHE PATH "cmake tmp dir")
    message("dir: ${dir}")

    # string
    set(str "hello cmake" CACHE STRING "a demo string")
    message("str: ${str}")

    # internal
    set(str02 "internal str" CACHE INTERNAL "an internal string")
    message("str02: ${str02}")
endfunction()

function(test_env_var)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
endfunction()

function(main)
    test_normal()
    test_cache_entry()
    test_env_var()
endfunction()

main()
