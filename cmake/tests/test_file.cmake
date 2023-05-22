# learning cmake foreach loop
# run: cmake -P file.cmake
# 2023-05-22

function(test_filesystem)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # find files in dir
    file(GLOB txtfiles /tmp/*.txt)
    message("/tmp .txt files: ${txtfiles}")
endfunction()

function(main)
    test_filesystem()
endfunction()

main()
