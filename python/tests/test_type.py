#!/usr/bin/python3
################################################################################
# python练习：获取参数类型
# python版本：python 3.6.9
# 时间：2023-03-13
################################################################################
import os
import sys
#import subprocess

# 获取参数类型
def test_var_type():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # <class 'int'>
    a = 3
    print("var type:", type(a))
    if isinstance(a, int):
        print("var type is int")
    else:
        print("var type is not int")

    # <class 'bool'>
    ret = True
    print("var type:", type(ret))
    if bool(ret):
        print("var type is bool")
    else:
        print("var type is not bool")

    # <class 'str'>
    str01 = "hello"
    print("var type:", type(str01))
    if isinstance(str01, str):
        print("var type is str")
    else:
        print("var type is not str")

    # <class 'list'>
    l = ["Tom", "Bob", "Jerry"]
    print("var type:", type(l))
    if isinstance(l, list):
        print("var type is list")
    else:
        print("var type is not list")

def main():
    test_var_type()

if __name__ == '__main__':
    main()
