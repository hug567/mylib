################################################################################
# python练习：获取参数类型
# python版本：python 3.6.9
# 时间：2023-03-13
################################################################################
import os
import sys
#import subprocess

# 获取参数类型
def test_var_type():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    a = 3
    print("var a type:", type(a))

def main():
    test_var_type()

if __name__ == '__main__':
    main()
