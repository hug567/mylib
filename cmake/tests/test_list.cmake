# learning cmake list
# run: cmake -P test_list.cmake
# 2023.05.16

function(test_list_reading)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(name Bob Tom Alice)
    message("name: ${name}")

    # get list length
    list(LENGTH name len)
    message("name list length: ${len}")

    # index from 0, get element 0
    list(GET name 0 name01)
    message("name[0]: ${name01}")
    # get element 0 and 1, return is a sub list
    list(GET name 0 1 name01)
    message("name[0,1]: ${name01}")
    # get element 0 and 2
    list(GET name 0 2 name01)
    message("name[0,2]: ${name01}")

    # modify list default separator ; to /
    list(JOIN name / name01)
    message("name01: ${name01}")

    # get sublist, start from index 1 and length is 2
    list(SUBLIST name 1 2 name01)
    message("name01: ${name01}")
endfunction()

function(test_list_search)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    set(name Bob Tom Alice)
    message("name: ${name}")

    # find element in list, return element index in list
    list(FIND name Tom index)
    if(${index} GREATER_EQUAL 0)
        message("find Tom in list name, element index: ${index}")
    endif()

    # does not find element in list, set index to -1
    list(FIND name Tomxx index)
    if(${index} EQUAL -1)
        message("does not find Tomxx in list name, index: ${index}")
    endif()
endfunction()

function(test_list_modify)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
    set(num 0 1 2 3 4)
    message("num: ${num}")

    # append to tail
    list(APPEND num 5)
    message("after append, num: ${num}")

    # insert to index 2, start from 0
    list(INSERT num 2 6)
    message("after insert, num: ${num}")
endfunction()

function(test_list_ordering)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")
endfunction()

function(main)
    test_list_reading()
    test_list_search()
    test_list_modify()
    test_list_ordering()
endfunction()

main()
