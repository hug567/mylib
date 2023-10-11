#!/usr/bin/python3
# 练习: 字符串替换
# 时间：2023-10-11

import re
import sys

#字符串搜索替换
def test_replace():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    str1 = "Hello, my name is Tom, his name is also Tom!"
    # 所有匹配的字符均替换
    str2 = str1.replace("Tom", "Bob")
    print("str1: [" + str1 + "]")
    print("str2: [" + str2 + "]")

    # 只替换指定个子串
    str3 = str1.replace("Tom", "Jerry", 1)
    # 替换为空字符串
    str3 = str3.replace("also ", "", 1)
    print("str3: [" + str3 + "]")

# 正则表达式搜索替换
def test_regular_replace():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    string = "My name is Tom xxxxx Bob"
    strinfo = re.compile('Tom.*Bob')
    replacestr = strinfo.sub('Jerry', string, 1)
    print("replacestr: [" + replacestr + "]")

def main():
    test_replace()
    test_regular_replace()

if __name__ == '__main__':
    main()
