#!/usr/bin/python3
# 2024-09-13

import sys

# 去除浮点数末尾的0和小数点
def test_strip_zero():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    print('{:g}'.format(123.0))
    print('{:g}'.format(45.6700))
    print('{:g}'.format(789))
    var = '{:g}'.format(789)
    print(type(var)) # 类型为<class 'str'>

def main():
    test_strip_zero()

if __name__ == '__main__':
    main()
