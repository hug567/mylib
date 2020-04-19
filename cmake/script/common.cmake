# 默认log日志文件
set(log_file "/tmp/cmake.log")

function(mt_log msg)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    message("[${cur_time}][INFO ][LINE:${CMAKE_CURRENT_LIST_LINE}]: ${msg}")
endfunction(mt_log)

function(mt_info msg)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    message("[${cur_time}][INFO ][LINE:${CMAKE_CURRENT_LIST_LINE}]: ${msg}")
endfunction(mt_info)

function(mt_error msg)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    message("[${cur_time}][ERROR][LINE:${CMAKE_CURRENT_LIST_LINE}]: ${msg}")
endfunction(mt_error)

function(mt_var var)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    message("[${cur_time}][INFO ][LINE:${CMAKE_CURRENT_LIST_LINE}]: ${var} = ${${var}}")
endfunction(mt_var)

function(mt_file msg)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    file(APPEND ${log_file} "[${cur_time}][INFO ][LINE:${CMAKE_CURRENT_LIST_LINE}]: ${msg}\n")
endfunction(mt_file)

function(mt_file_var var)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    file(APPEND ${log_file} "[${cur_time}][INFO ][LINE:${CMAKE_CURRENT_LIST_LINE}]: ${var} = ${${var}}\n")
endfunction(mt_file_var)
