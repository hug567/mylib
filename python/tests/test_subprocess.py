#!/usr/bin/python3

################################################################################
# learning python subprocess
# python 3.6.9
# 2023-04-23
################################################################################

import os
import sys
import subprocess

def test_run():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    files = subprocess.run('ls -l', shell=True, stdout=subprocess.PIPE)
    print(files)

def test_call():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # print result to stdout, ret is simply the return value of command execution
    ret = subprocess.call("pwd", shell=True)
    print("call ret:", ret) # 0: success, !0: fail

def test_popen():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    files=subprocess.Popen("ls -l", shell=True)
    files.wait()
    print(type(files))

    # wait for cmd run finish
    print("will sleep 5s")
    p = subprocess.Popen("sleep 5", shell=True)
    ret = p.wait()
    print("cmd ret:", ret)

def main():
    test_call()
    test_run()
    test_popen()

if __name__ == '__main__':
    main()
