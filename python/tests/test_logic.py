#!/usr/bin/python3
# python逻辑运算：与,或,非
# 2024-10-10

import sys

# 单个逻辑运算
def test_single_logic():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    num1 = 10
    num2 = 15

    # 与：and
    if num1 == 10 and num2 == 15:
        print('num1 is 10 and num2 is 15')

    # 或：or
    if num1 == 9 or num1 == 10:
        print('num1 is 9 or 10')

    # 非：not
    if not num1 == 9:
        print('num1 is not 9')

def main():
    test_single_logic()

if __name__ == '__main__':
    main()
