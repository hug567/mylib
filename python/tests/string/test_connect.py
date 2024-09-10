#!/usr/bin/python3
# 练习: 字符串连接
# 时间：2023-10-10

import sys

def test_str_connect():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 字符串连接
    name = "Huang" + " " + "Xing"
    print("My name is:", name)

# 长字符串换行
def test_str_lines():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    info = 'My name is Tom, ' + \
           'and my age is 18'
    print('info:', info)

def main():
    test_str_connect()
    test_str_lines()

if __name__ == '__main__':
    main()
