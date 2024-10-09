#!/usr/bin/python3
# 从其他文件中引入python模块
# python查找模块的顺序：
#   1、执行脚本的当前目录
#   2、内置模块
#   3、sys.path中的路径，包括
#     1）、安装目录中的site-packages目录
#     2）、环境变量PYTHONPATH中定义的路径
#     3）、标准库的路径
# 2024-10-09

# 引入python自带的整个模块
import os
import sys
# 引入当前目录下的student包，student是py文件的文件名
import student
# 引入模块并创建别名
import student as stu
# 从子目录sub中引入包teacher
from sub import teacher
# 从多级子目录中引入包worker
from sub.sub2 import worker
# 引入包中的部门成员，并设置别名
from driver import print_name as driver_print_name
from driver import print_age as driver_print_age
# 从上级目录引入模块，将上级目录的绝对路径添加到sys.path变量中
current_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.abspath(os.path.join(current_dir, '..'))
sys.path.append(parent_dir)
import cleaner

def test_pkg_student():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 使用引入的student模块中的函数
    student.print_name('Tom')
    # 通过别名使用引入的模块
    stu.print_age(18)

def test_pkg_teacher():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 使用引入的模块中的函数
    teacher.print_name('Bob')
    teacher.print_age(23)

def test_pkg_worker():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 使用引入的模块中的函数
    worker.print_name('Jerry')
    worker.print_age(28)

def test_pkg_driver():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 使用引入的模块中的函数
    driver_print_name('Alice')
    driver_print_age(30)

def test_pkg_cleaner():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 使用引入的模块中的函数
    cleaner.print_name('John')
    cleaner.print_age(27)

def main():
    test_pkg_student()
    test_pkg_teacher()
    test_pkg_worker()
    test_pkg_driver()
    test_pkg_cleaner()

if __name__ == '__main__':
    main()
