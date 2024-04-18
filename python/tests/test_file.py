#!/usr/bin/python3
################################################################################
# python练习：文件
# python版本：python 3.6.9
# 时间：2021-11-21
################################################################################
import os
import sys
import shutil

def learning_file():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    file_name = 'rfile.txt'
    if not os.path.exists(file_name):
        return

    # 读取文件
    with open(file_name) as file_obj:
        contents = file_obj.read()
        print(contents)

    # 读取文件
    fobj = open(file_name)
    cts = fobj.read()
    print(cts)

    # 逐行读取
    with open(file_name) as file_obj:
        for line in file_obj:
            print(line, end='')

    # 读取文件至以行为元素的列表
    with open(file_name) as file_obj:
        lines = file_obj.readlines()
        print(lines)
        # 遍历列表
        for line in lines:
            print(line.rstrip())

    wfname = 'wfile.out'

    # 写入文件
    with open(wfname, 'w') as file_obj:
        file_obj.write("practice python write to file\n")
        file_obj.write("write second line\n")
    with open(wfname) as file_obj:
        print(file_obj.read(), end='', sep='')

    # 附加到文件
    with open(wfname, 'a') as file_obj:
        file_obj.write("append third line to file\n")
    with open(wfname) as file_obj:
        print(file_obj.read(), end='', sep='')

    # 删除文件
    os.remove(wfname)

# 判断文件是否存在
def check_file_exist(fname):
    if os.path.exists(fname):
        print("file", fname, "exist")
    else:
        print("file", fname, "does not exist")

# 创建和删除文件
def create_delete_file():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 需先有目录
    fname="/tmp/python_test.txt"
    # 创建文件
    file = open(fname, 'w')
    check_file_exist(fname)
    file.close()
    # 删除文件
    os.remove(fname)
    check_file_exist(fname)

# 检查目录是否存在
def check_dir_exist(dname):
    if os.path.exists(dname):
        print("dir", dname, "exist")
    else:
        print("dir", dname, "does not exist")

# 创建和删除目录
def create_delete_dir():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    dname = "/tmp/python_test/test01/test01_01"
    check_dir_exist(dname)
    if not os.path.exists(dname):
        # 递归创建嵌套子目录
        os.makedirs(dname)
    check_dir_exist(dname)
    # 删除非空目录
    shutil.rmtree("/tmp/python_test")
    check_dir_exist(dname)

# 重命名文件
def test_rename_file():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    fname = "/tmp/test_python.txt"
    new_fname = "/tmp/test_python_new.txt"
    if not os.path.exists(fname):
        file = open(fname, 'w')
        file.close()
    if os.path.exists(new_fname):
        os.remove(new_fname)
    # 重命名文件
    print("will rename file from", fname, "to", new_fname)
    os.rename(fname, new_fname)

def main():
    learning_file()
    create_delete_file()
    create_delete_dir()
    test_rename_file()

if __name__ == '__main__':
    main()
