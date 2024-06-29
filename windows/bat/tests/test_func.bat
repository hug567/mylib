::bat函数

::不回显命令
@echo off

::打印
echo hello world!

::调用函数
call :myFunc

::调用函数传入参数
call :printParams var1

::调用带返回值函数
call :funcWithReturnVal
@echo func return value: %return%

::暂停
pause
::退出当前脚本
exit

::---------------------------------------------------------------------------::
::定义函数，放在脚本最后
:myFunc
    @echo Enter custom function
@goto:eof

::带参数的函数
:printParams
    ::定义变量
    set var1=%~1
    ::引用变量
    @echo parma 1: %var1%
@goto:eof

::带返回值的函数
:funcWithReturnVal
    set return=returnVal
@goto:eof
::---------------------------------------------------------------------------::
