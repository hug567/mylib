::bat文件相关

::不回显命令
@echo off

call :log_info "print info level log"

::调用函数
call :checkFileExist test_file.bat
call :checkFileExist file.txt
echo ------------------------

::暂停
pause
::退出当前脚本
exit

::---------------------------------------------------------------------------::
::检查文件是否存在
:checkFileExist
    set file=%1
    if not exist %file% (
        echo file [%file%] does not exist
        pause
        exit
    )
goto:eof

:log_info
    for /f "delims=" %%i in ('date') do set time=%%i
    echo %time%
    echo [('date')^][INFO ] %~1
goto:eof
::---------------------------------------------------------------------------::
