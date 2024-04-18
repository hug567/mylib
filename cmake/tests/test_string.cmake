# cmake字符串基本操作
# 执行脚本：cmake -P test_strcmp.cmake
# 2024-04-18

# 字符串比较
function(test_str_cmp)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
    set(var1 "test_var")
    set(var2 "test_var")

    # 比较字符串是否相等
    if(${var1} STREQUAL ${var2})
        message("var1 is same as var2")
    else()
        message("var1 is not same as var2")
    endif()
endfunction()

# 判断字符串是否为空
function(test_str_empty)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(var1 "")
    set(var3 "test_var")

    # 字符串为空
    if ("${var1}" STREQUAL "")
        message("var1 is empty")
    endif ()
    message("var2 is not defined")
    if ("${var2}" STREQUAL "")
        message("var2 is empty")
    endif ()

    # 字符串不为空
    if (NOT "x${var3}" STREQUAL "x")
        message("var3 is not empty")
    endif ()
endfunction()

function(main)
    test_str_cmp()
    test_str_empty()
endfunction()

main()
