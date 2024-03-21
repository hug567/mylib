#!/usr/bin/python3

################################################################################
# python练习：执行shell命令
# python版本：python 3.6.9
# 时间：2023-01-31
################################################################################
import os
import sys
import subprocess

# shell命令结果实时输出
def run_shell_realtime_output(cmd):
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

# 运行shell命令后结果在python函数中返回
def run_shell_return_result(cmd):
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
    # wait for the shell cmd to finish
    p.wait()
    return output

#------------------------------------------------------------------------------#
# python中不能获取命令执行结果
def test_os_system():
    print("test_os_system: --------------------------")
    os.system('pwd')
    ret = os.system('ls &')

# python中可以获取命令执行结果
def test_os_popen():
    print("test_os_popen: ---------------------------")
    f = os.popen('pwd')
    print(f.read())
    f = os.popen('ls')
    print(f.read())

# 通过子进程执行外部命令
def test_subprocess():
    print("test_subprocess: -------------------------")
    # 直接输出命令结果，并返回命令执行是否成功
    ret = subprocess.call("pwd", shell=True)
    print("call ret:", ret) # 0: success, !0: fail

def test_run_shell_return_result():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    output = run_shell_return_result('ls -l /')
    for line in output:
        print(line)
    #print(output[0]) # 第一行


def main():
    test_os_system()
    test_os_popen()
    test_subprocess()
    test_run_shell_return_result()

if __name__ == '__main__':
    main()
