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

# eg: log_info_var(CMAKE_CURRENT_SOURCE_DIR)
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


# 单个文件编译成单个文件的测试用例
# 文件名包可含：大小写字母、数字、下划线、横线
# eg:
# compile_single_file(
#     file1.c
#     file2.c
# )
function(compile_single_file)
    set(index 0)
    while(index LESS ${ARGC})
        set(file ${ARGV${index}})
        string(REGEX MATCH "[A-Za-z0-9_-]+\.c$" file_bin ${file})
        string(REGEX MATCH "^[A-Za-z0-9_-]+" file_bin ${file_bin})
        add_executable(${file_bin} ${file})
        math(EXPR index "${index} + 1")
    endwhile()
endfunction(compile_single_file)
