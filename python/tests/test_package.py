#!/usr/bin/python3
################################################################################
# python练习：包相关操作
# python版本：python 3.6.9
# 时间：2023-01-29
################################################################################
import os
import sys

# 打印包文件路径
def test_get_package_file_pos():
    print("package sys file position: ", os.__file__, sep='')

def main():
    test_get_package_file_pos()

if __name__ == '__main__':
    main()
