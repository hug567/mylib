#!/usr/bin/python3
# 练习: 字符串连接
# 时间：2023-10-10

import sys

def test_str_connect():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 字符串连接
    name = "Huang" + " " + "Xing"
    print("My name is:", name)

def main():
    test_str_connect()

if __name__ == '__main__':
    main()
