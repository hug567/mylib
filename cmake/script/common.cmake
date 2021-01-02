# 默认log日志文件
set(log_file "/tmp/cmake.log")

function(mt_log msg)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    message("[${cur_time}][INFO ]: ${msg}")
endfunction(mt_log)

function(log_info msg)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    message("[${cur_time}][INFO ]: ${msg}")
endfunction(log_info)

function(log_error msg)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    message("[${cur_time}][ERROR]: ${msg}")
endfunction(log_error)

function(log_info_var var)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    message("[${cur_time}][INFO ]: ${var} = ${${var}}")
endfunction(log_info_var)

function(log_info_to_file msg)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    file(APPEND ${log_file} "[${cur_time}][INFO ]: ${msg}\n")
endfunction(log_info_to_file)

function(mt_file_var var)
    execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE cur_time)
    string(REPLACE "\n" "" cur_time ${cur_time})
    file(APPEND ${log_file} "[${cur_time}][INFO ]: ${var} = ${${var}}\n")
endfunction(mt_file_var)
