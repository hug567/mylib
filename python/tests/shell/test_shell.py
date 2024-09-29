#!/usr/bin/python3

################################################################################
# python练习：执行shell命令
# python版本：python 3.6.9
# 时间：2023-01-31
################################################################################
import os
import sys
import subprocess

#------------------------------------------------------------------------------#
# shell命令结果实时输出，并返回是否执行成功
def run_cmd_realtime_output(cmd):
    output = []
    # run shell cmd
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                         stderr=subprocess.STDOUT)
    # realtime output
    while True:
        line = p.stdout.readline()
        if not line:
            break
        output.append(line.strip().decode('utf-8'))
        print(output[-1])
    # wait for the shell cmd to finish
    p.wait()
    # 返回shell命令执行结果，0：成功，!0：失败
    return p.returncode

# 运行shell命令后，返回执行结果，及命令是否执行成功
def run_cmd_return_result(cmd):
    output_str = ""
    # 执行shell命令
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                         stderr=subprocess.STDOUT)
    while True:
        # 逐行获取命令执行结果
        line = p.stdout.readline()
        if not line:
            break
        # 将返回行转换为字符串
        output_str = output_str + line.strip().decode('utf-8') + '\n'
    # 等待执行完成
    p.wait()
    # 获取命令执行结果，0：成功，!0：失败
    ret = p.returncode
    # 返回命令是否执行成功，以及命令执行的输出
    return ret, output_str.strip()

def test_run_shell_and_check_success():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    cmd = "ls /"
    ret = run_cmd_realtime_output(cmd)
    print("run shell cmd: [" + cmd + "], return value:", ret)
    if not ret:
        print("run shell cmd: [" + cmd + "] success")

    cmd = "ls /xx"
    ret = run_cmd_realtime_output(cmd)
    print("run shell cmd: [" + cmd + "], return value:", ret)
    if ret:
        print("run shell cmd: [" + cmd + "] failed")

def test_run_shell_return_result():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    cmd = 'ls -l /'
    ret, output = run_cmd_return_result(cmd)
    if ret == 0:
        print("run shell cmd success:", cmd)
    else:
        print("run shell cmd fail:", cmd)
    print(output)

    cmd = 'ls -l /xx'
    ret, output = run_cmd_return_result(cmd)
    if ret == 0:
        print("run shell cmd success:", cmd)
    else:
        print("run shell cmd fail:", cmd)
    print(output)

#------------------------------------------------------------------------------#
# 通过子进程执行外部命令
def test_subprocess():
    print("test_subprocess: -------------------------")
    # 直接输出命令结果，并返回命令执行是否成功
    ret = subprocess.call("pwd", shell=True)
    print("call ret:", ret) # 0: success, !0: fail

#------------------------------------------------------------------------------#
# python中不能获取命令执行结果
def test_os_system():
    print("test_os_system: --------------------------")
    os.system('pwd')
    # 只能将执行命令打印到标准输出，并返回是否成功，不能捕获命令输出
    ret = os.system('ls &')

#------------------------------------------------------------------------------#
# python中可以获取命令执行结果
def test_os_popen():
    print("test_os_popen: ---------------------------")
    f = os.popen('pwd')
    print(f.read())
    f = os.popen('ls')
    print(f.read())

#------------------------------------------------------------------------------#
def main():
    test_os_system()
    test_os_popen()
    test_subprocess()
    test_run_shell_return_result()
    test_run_shell_and_check_success()

if __name__ == '__main__':
    main()
