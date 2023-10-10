#!/usr/bin/python3
# 练习: 字符串替换
# 时间：2023-10-10

import re
import sys

# 正则表达式搜索替换
def test_regular_replace():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    string = "My name is Tom xxxxx Bob"
    strinfo = re.compile('Tom.*Bob')
    replacestr = strinfo.sub('Jerry', string, 1)
    print("replacestr: [" + replacestr + "]")

def main():
    test_regular_replace()

if __name__ == '__main__':
    main()
