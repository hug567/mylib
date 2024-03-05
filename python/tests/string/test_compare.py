#!/usr/bin/python3
# 练习: 字符串比较
# 时间：2024-03-05

import sys

# 字符串比较，区分大小写
def test_compare():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 相等
    str1="hello"
    str2="hello"
    if str1 == str2:
        print("str1 is same as str2")

    # 不等
    str3="hello"
    str4="world"
    if str3 != str4:
        print("str3 is not same as str4")

    # 比较：>，>=，<，<=

def main():
    test_compare()

if __name__ == '__main__':
    main()
