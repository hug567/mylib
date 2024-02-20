#!/usr/bin/python3
# 练习: 字符串查找
# 时间：2023-10-11

import re
import sys

#字符串搜索
def test_find():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    str1 = "My name is Tom!"
    if str1.find("Tom") >= 0:
        print("find \'Tom\' in str \'" + str1 + "\'")

    # 查找的子串中包含空格
    if str1.find(" is") >= 0:
        print("find \'name is\' in str \'" + str1 + "\'")

#使用正则表达式搜索
def test_search():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 正则表达式从头部开始查找
    str1 = "My name is Tom!"
    if re.search('^My', str1) is not None:
        print("find \'My\' in str head: \'" + str1 + "\'")
    str2 = "str: My name is Tom!"
    if re.search('^My', str2) is None:
        print("does not find \'My\' in str head: \'" + str2 + "\'")

def main():
    test_find()
    test_search()

if __name__ == '__main__':
    main()
