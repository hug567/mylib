# learning cmake run shell cmd
# run: cmake -P test_shell.cmake
# 2023.05.16

function(test_shell)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # Execute commands in serial
    execute_process(COMMAND echo -n "current path: ")
    execute_process(COMMAND pwd)
    execute_process(COMMAND ls -l)
    execute_process(COMMAND rm -rf CMakeCache.txt CMakeFiles COMMAND_ECHO STDOUT)

    # Multiple COMMAND will be executed in parallel
    execute_process(COMMAND ls -l /tmp/vim_tmp.txt
                    COMMAND ls -l)
endfunction()

# add_custom_command
# add_custom_target

function(main)
    test_shell()
endfunction()

main()
