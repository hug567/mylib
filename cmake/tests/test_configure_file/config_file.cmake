# 测试cmake库函数configure_file()
# 运行：cmake -P configure_file.cmake
# 2024-08-07

function(test_configure_file)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
endfunction()

function(main)
    test_configure_file()
endfunction()

main()
