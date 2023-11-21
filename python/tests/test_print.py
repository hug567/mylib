#!/usr/bin/python3
################################################################################
# python练习：print常用操作
# python版本：python 3.6.9
# 时间：2023-01-31
################################################################################
import os
import sys

# number, string, list,...

def test_print_string():
    # 默认换行
    print("hello world!")

    # 不换行
    print("1 + 1 = ", end='')
    print("2")

    # 默认分割符为空格
    num = 12345
    print("[1] num =", num)
    # 不带分隔符
    print("[2] num = ", num, sep='')

# 格式化输出
def test_print_format():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    name = "Tom"
    age = 18
    # 格式化输出字符串
    print("name: %s" % name)
    # 格式化输出多个变量
    print("name: %s, age: %d" % (name, age))

def main():
    test_print_string()
    test_print_format();

if __name__ == '__main__':
    main()
