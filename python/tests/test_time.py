#!/usr/bin/python3
# python时间相关操作
# 2024-12-26

import sys
import time

def test_print_time():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 自1970.1.1以来的秒数
    print(time.time())
    # 打印本地时间
    print(time.localtime(time.time()))
    # 格式化的时间
    print(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())))

def main():
    test_print_time()

if __name__ == '__main__':
    main()
