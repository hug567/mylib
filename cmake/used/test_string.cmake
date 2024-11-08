# cmake字符串操作
# 运行: cmake -P test_string.cmake
# 2024-11-08

# 字符串分割
function(test_string_split)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(str01 "CONFIG_PLATFORM_TEST")
    string(REPLACE "_" ";" platform ${str01})
    list(GET platform -1 platform_short)
    message("platform_short: ${platform_short}")
endfunction()

function(main)
    test_string_split()
endfunction()

main()
