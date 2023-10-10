#!/usr/bin/python3
# 练习：处理shell命令的结果字符串
# 时间：2023-10-10

import os
import re
import sys

def test_cmd_result():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # result类型是string
    result = os.popen('ls -l /home/hx').read().strip()
    # lines类型是list
    lines = result.split('\n')
    # 删除首行
    del lines[0]
    retstr = ""
    # 遍历列表
    for line in lines:
        if len(line) == 0:
            continue
        # 字符串正则表达式搜索替换
        strinfo = re.compile('^.* hx')
        replacestr = strinfo.sub('', line, 1)
        # 字符串连接
        retstr = retstr + replacestr + '\n'

    # 去除首尾空白符
    print(retstr.strip())

def main():
    test_cmd_result()

if __name__ == '__main__':
    main()
