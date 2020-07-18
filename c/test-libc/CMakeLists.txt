# cmake最低版本要求
cmake_minimum_required(VERSION 2.6)

# cmake工程名称
project(test-libc)

add_executable(test-libc.elf
    main.c
    test.c

    # array
    array/array_main.c
    array/test_array.c
    array/test_func_param.c

    # file
    file/file_main.c
    file/test_write.c

    # stdio
    stdio/stdio_main.c
    stdio/test_sizeof.c

    # stdlib
    stdlib/stdlib_main.c
    stdlib/test_qsort.c
    stdlib/test_qsort2.c

    # string
    string/string_main.c
    string/test_strlen.c
)
