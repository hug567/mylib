#!/usr/bin/python3
# 练习: 字符串查找
# 时间：2023-10-11

import sys

#字符串搜索替换
def test_find():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    str1 = "My name is Tom!"
    if str1.find("Tom") >= 0:
        print("find \'Tom\' in str \'" + str1 + "\'")

def main():
    test_find()

if __name__ == '__main__':
    main()
