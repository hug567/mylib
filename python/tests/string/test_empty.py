#!/usr/bin/python3
# 练习：判断字符串是否为空
# 时间：2023-10-11

import sys

# 判断字符串是否为空
def test_str_empty():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    str1 = ""
    str2 = "hello"

    if len(str1) == 0:
        print("\'str1\' is empty")
    if len(str2) > 0:
        print("\'str2\' is not empty: " + str2)

def main():
    test_str_empty()

if __name__ == '__main__':
    main()
