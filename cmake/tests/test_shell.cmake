# learning cmake run shell cmd
# run: cmake -P test_shell.cmake
# 2023.05.16

function(test_shell)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
    execute_process(COMMAND echo -n "current path: ")
    execute_process(COMMAND pwd)
    execute_process(COMMAND ls -l)
    execute_process(COMMAND rm -rf CMakeCache.txt CMakeFiles)
endfunction()

function(main)
    test_shell()
endfunction()

main()
