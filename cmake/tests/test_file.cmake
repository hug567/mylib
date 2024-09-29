# learning cmake foreach loop
# run: cmake -P file.cmake
# 2023-05-22

function(test_filesystem)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # find files in dir
    file(GLOB txtfiles /tmp/*.txt)
    message("/tmp .txt files: ${txtfiles}")
endfunction()

# 判断文件是否存在
function(test_file_exist)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    #绝对路径文件
    set(fname "/tmp/test.cmake")
    if(EXISTS ${fname})
        message("file ${fname} exists")
    else()
        message("file ${fname} does not exist")
    endif()

    # 相对当前路径的文件
    # CMAKE_CURRENT_SOURCE_DIR需在CMakeLists.txt中文件才表示源文件所在目录
    # 在.cmake文件，且用cmake命令直接执行.cmake脚本，表示执行命令时的当前目录
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test_file.cmake")
        message("file ${CMAKE_CURRENT_SOURCE_DIR}/test_file.cmake exists")
    endif()
endfunction()

function(main)
    test_filesystem()
    test_file_exist()
endfunction()

main()
