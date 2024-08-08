# cmake布尔变量
# 运行: cmake -P test_bool.cmake
# 2024-08-07

# camke函数返回布尔值：真/假
function(is_larger_10 num ret)
    if(${num} GREATER 10)
        set(${ret} TRUE PARENT_SCOPE)
    else()
        set(${ret} FALSE PARENT_SCOPE)
    endif()
endfunction()

function(test_func_ret_bool)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(num 5)
    set(ret) # 存储函数返回的布尔值
    is_larger_10(${num} ret)
    if(ret) # 判断函数返回的布尔值
        message("${num} > 10")
    else()
        message("${num} <= 10")
    endif()

    set(num 15)
    is_larger_10(${num} ret)
    if(ret) # 判断函数返回的布尔值
        message("${num} > 10")
    else()
        message("${num} <= 10")
    endif()

endfunction()

function(main)
    test_func_ret_bool()
endfunction()

main()
