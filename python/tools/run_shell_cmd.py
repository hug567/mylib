#!/usr/bin/python3
# run shell cmd in python
# 2023-06-26

import os
import sys
import subprocess

# 需求：
# 1、只需执行命令，不需要知道是否执行成功
# 2、需要知道指定执行成功
# 3、只需要获取命令打印
# 4、需要获取命令打印，并获取命令是否执行成功
# 5、不需要获取命令结果，实时输出到屏幕即可
# 6、实时输出结果，最后获取命令是否执行成功

def run_only_run(cmd):
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                         stderr=subprocess.STDOUT)
    p.wait()

def run_whether_success(cmd):
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                         stderr=subprocess.STDOUT)
    return not p.wait()

def run_only_get_result(cmd):
    result = []
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                         stderr=subprocess.STDOUT)
    while True:
        line = p.stdout.readline()
        if not line:
            break
        result.append(line.decode('utf-8').strip('\n'))
    p.wait()
    return result

def run_whether_success_and_result(cmd):
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                         stderr=subprocess.STDOUT)
    while p.poll() is None:
        if p.wait() != 0:
            return False
        else:
            result = []
            lines = p.stdout.readlines()
            for line in lines:
                result.append(line.decode('utf-8').strip('\n'))
            return result

def run_realtime_result(cmd):
    result = []
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                         stderr=subprocess.STDOUT)
    while True:
        line = p.stdout.readline()
        if not line:
            break
        result.append(line.decode('utf-8').strip('\n'))
        print(result[-1])
    p.wait()

def run_whether_success_realtime_result(cmd):
    result = []
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                         stderr=subprocess.STDOUT)
    while True:
        line = p.stdout.readline()
        if not line:
            break
        result.append(line.decode('utf-8').strip('\n'))
        print(result[-1])
    return not p.wait()

################################################################################
def test_run_cmd():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    print("run_only_run: ----------")
    print("touch and rm file: /tmp/test_run_cmd.txt")
    run_only_run('touch /tmp/test_run_cmd.txt')
    run_only_run('rm /tmp/test_run_cmd.txt')

    print("run_whether_success, success: ----------")
    if run_whether_success('ls /tmp'):
        print("run cmd success: ls /tmp")
    print("run_whether_success, failed: ----------")
    if run_whether_success('ls /xxx'):
        print("run cmd success: ls /xxx")
    else:
        print("run cmd failed: ls /xxx")

    print("run_only_get_result, success: ----------")
    ret = run_only_get_result('ls -l / | grep bin')
    for i in range(0, len(ret)):
        print(ret[i])
    print("run_only_get_result, failed: ----------")
    ret = run_only_get_result('ls -l /xxx')
    for i in range(0, len(ret)):
        print(ret[i])

    print("run_whether_success_and_result: ----------")
    ret = run_whether_success_and_result("ls -l / | grep etc")
    if isinstance(ret, list):
        print("run cmd success: ls -l / | grep etc")
        for i in range(0, len(ret)):
            print(ret[i])
    ret = run_whether_success_and_result("ls /xxx")
    if isinstance(ret, bool) and not ret:
        print("run cmd failed: ls /xxx")

    print("run_realtime_result: ----------")
    run_realtime_result("ping localhost -c 3")

    print("run_whether_success_realtime_result: ----------")
    if run_whether_success_realtime_result('ping localhost -c 3'):
        print("run cmd success: ping localhost -c 1")
    if not run_whether_success_realtime_result('ping 192.168.0.11 -c 10'):
        print("run cmd failed: ping 192.168.0.11 -c 10")

def main():
    test_run_cmd()

if __name__ == '__main__':
    main()
