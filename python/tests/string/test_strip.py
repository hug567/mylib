#!/usr/bin/python3
# 练习: 移除字符首尾的指定字符strip()
# 时间：2023-10-10

import sys

# 默认移除首尾的空格、Tab、换行符
def test_strip():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    string = "  \tHello\tWorld\t!\n"
    str_strip = string.strip()
    print("string:    [" + string + "]")
    print("str_strip: [" + str_strip + "]")

# 移除字符串首尾指定字符或字符串
def test_strip_by_char():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 移除指定字符，不再移除空格、Tab、换行符
    string = "xxxHello\tWorld\t!    "
    str_strip = string.strip('x')
    print("string:    [" + string + "]")
    print("str_strip: [" + str_strip + "]")

def test_strip_by_str():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # 移除首尾指定的字符串
    string = "Hello\tWorld\t!    xyzxyz"
    str_strip = string.strip('xyz')
    print("string:    [" + string + "]")
    print("str_strip: [" + str_strip + "]")

def main():
    test_strip()
    test_strip_by_char()
    test_strip_by_str()

if __name__ == '__main__':
    main()
