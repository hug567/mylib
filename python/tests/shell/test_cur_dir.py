#!/usr/bin/python3
# 获取当前python文件所在目录
# 2024-04-18

import os
import sys

def test_cur_dir():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    print("__file__:", __file__)
    cur_dir = os.path.dirname(__file__)
    print("cur_dir:", cur_dir)


def main():
    test_cur_dir()

if __name__ == '__main__':
    main()
