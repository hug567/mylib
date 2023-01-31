################################################################################
# python练习：执行shell命令
# python版本：python 3.6.9
# 时间：2023-01-31
################################################################################
import os
import subprocess

# python中不能获取命令执行结果
def test_os_system():
    print("test_os_system: --------------------------")
    os.system('pwd')
    os.system('ls')

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

def main():
    test_os_system()
    test_os_popen()
    test_subprocess()

if __name__ == '__main__':
    main()
