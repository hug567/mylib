#!/usr/bin/python3
# 练习: 字符串分割
# 时间：2023-10-10

import sys

def test_split_by_char():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 以空格分割字符串
    string = "You need to have a dream"
    str_split = string.split(' ')
    print(str_split)

    # 以空格、Tab、换行符分割字符串
    string = "You need to\nhave\ta dream"
    str_split = string.split()
    print(str_split)

def main():
    test_split_by_char()

if __name__ == '__main__':
    main()
