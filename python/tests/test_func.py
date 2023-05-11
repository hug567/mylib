#!/usr/bin/python3
################################################################################
# python练习：函数
# python版本：python 3.6.9
# 时间：2021-11-16
################################################################################
import sys
import time
import random

# 无参函数
def test_get_time():
    print("time: " + time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))

# 单个入参
def test_print_name(name):
    print("name: " + name)

# 多个入参
def test_print_position(x, y, z):
    print("position: (", x, ", ", y, ", ", z, ")", sep='') # 打印不自带空格

# 参数带默认值
def test_print_age(age=18):
    print("age: ", age, sep='')

# 返回简单值
def test_get_random():
    return random.randint(0, 100)

# 返回字典
def test_set_size(width, height):
    size = {"width" : width, "height" : height}
    return size

# 传递列表
def test_count(lst):
    lst[0] += 1

# 变长参数，将入参封装成了元组
def test_print_num(*nums):
    print("nums: ", nums, sep='')

# 获取当前文件名、函数名、行号
# import sys
def get_file_func_linenum():
    print("-------------------------------------------------------------------")
    print("file: ", sys._getframe().f_code.co_filename, sep='')
    print("function: ", sys._getframe().f_code.co_name, sep='')
    print("line number: ", sys._getframe().f_lineno, sep='')
    print("[hx-debug] exec location: ", sys._getframe().f_code.co_name, "()/", sys._getframe().f_lineno, sep='')
    print("[hx-debug] exec location: {", sys._getframe().f_code.co_filename, "}: ",
          sys._getframe().f_code.co_name, "()/", sys._getframe().f_lineno, sep='')

# 主函数
def main():
    test_get_time()
    test_print_name("dog")
    test_print_position(1, 2, 3)
    test_print_position(x=4, y=5, z=6) # 函数调用指定参数赋值
    test_print_age() # 形参有默认值，可不传实参
    print("random value: ", test_get_random(), sep='')
    print("size: ", test_set_size(10, 20), sep='')
    count=[6, 7, 8, 9]
    print(count)
    test_count(count) # 传入列表，在函数中可修改列表成员值
    print(count)
    test_count(count[:]) # 传入列表副本，在函数中修改列表成员值不影响外部列表
    print(count)
    test_print_num(10)
    test_print_num(10, 11)
    test_print_num(10, 11, 12)
    get_file_func_linenum()

main()
