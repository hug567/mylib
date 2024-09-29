#!/usr/bin/python3
################################################################################
# python练习：函数
# python版本：python 3.6.9
# 时间：2021-11-16
################################################################################
import sys
import time
import random

# python函数参数类型：必选参数、默认参数、可选参数、关键字惨、命名关键字参数

# 无参函数
def test_get_time():
    print("time: " + time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))

# 单个入参(必选参数)
def test_print_name(name):
    print("name: " + name)

# 多个入参(必选参数)
def test_print_position(x, y, z):
    print("position: (", x, ", ", y, ", ", z, ")", sep='') # 打印不自带空格

# 参数带默认值(可选参数)
def test_print_age(age=18):
    print("age: ", age, sep='')

# 可变参数
def numbers_sum(*nums):
    sum = 0
    for n in nums:
        sum += n
    print("sum =", sum)

def test_variable_params():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # 传入3个参数
    numbers_sum(1, 2, 3)
    # 传入4个参数
    numbers_sum(4, 5, 6, 7)

# 关键字参数，键值任意
def key_params(name, age, **kw):
    print("name:", name, ", age:", age)
    if 'height' in kw:
        print("height:", kw["height"])

def test_key_params():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    key_params("Tom", 18)
    key_params("Jerry", 20, height=183)

# 命名关键字参数，键值固定
def name_key_params(name, age, *, city):
    print("name:", name, ", age:", age)
    print("city:", city)

def test_name_key_params():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    name_key_params("Alice", 23, city="Hefei")

# 返回随机值
def test_get_random():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    num = random.randint(0, 100)
    print("random num:", num)

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
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    print("file: ", sys._getframe().f_code.co_filename, sep='')
    print("function: ", sys._getframe().f_code.co_name, sep='')
    print("line number: ", sys._getframe().f_lineno, sep='')
    print("[hx-debug] exec location: ", sys._getframe().f_code.co_name, "()/", sys._getframe().f_lineno, sep='')
    print("[hx-debug] exec location: {", sys._getframe().f_code.co_filename, "}: ",
          sys._getframe().f_code.co_name, "()/", sys._getframe().f_lineno, sep='')

#------------------------------------------------------------------------------#
# python函数返回多个值
def _return_multi():
    x = 10
    y = 20
    z = 30
    return x, y, z

def test_return_multi():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 调用返回多个值的函数
    x, y, z = _return_multi()
    print("x:", x, "y:", y, "z:", z)

    # 多个返回值存储在一个变量中，该变量是一个元组，包含多个返回值
    ret = _return_multi()
    print("ret:", ret)
#------------------------------------------------------------------------------#

# 主函数
def main():
    test_get_time()
    test_print_name("dog")
    test_print_position(1, 2, 3)
    test_print_position(x=4, y=5, z=6) # 函数调用指定参数赋值
    test_print_age() # 形参有默认值，可不传实参
    test_variable_params()
    test_key_params()
    test_name_key_params()
    test_get_random()
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
    test_return_multi()

main()
