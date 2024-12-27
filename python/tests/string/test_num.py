#!/usr/bin/python3
# 练习: 字符串与数字互相转换
# 时间：2023-10-10

import sys

def test_str_to_int():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    str1 = '1234'
    num1 = int(str1)
    print("num1 type: ", type(num1), ", num1 = ", num1, sep='')

    str2 = '005678'
    num2 = int(str2)
    print("num2 type: ", type(num2), ", num2 = ", num2, sep='')

# 字符串转浮点数
def test_str_to_float():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    str1 = '1234.56'
    num1 = float(str1)
    print("num1 type: ", type(num1), ", num1 = ", num1, sep='')

    str2 = '78.900'
    num2 = float(str2)
    print("num2 type: ", type(num2), ", num2 = ", num2, sep='')

# 浮点数转字符串
def test_float_to_string():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    num1 = 1234.56
    str1 = str(num1)
    print("str1 type: ", type(str1), ", str1 = ", str1, sep='')

    num2 = 78.900
    str2 = str(num2)
    print("str2 type: ", type(str2), ", str2 = ", str2, sep='')

    # 浮点型整数转字符串，会在小数点后保留1个0
    num1 = 234.00009
    str1 = str(num1)
    print("str1 type: ", type(str1), ", str1 = ", str1, sep='')
    # 去除末尾的.0
    str1 = str(num1).rstrip('0').rstrip('.')
    print("str1 type: ", type(str1), ", str1 = ", str1, sep='')

def main():
    test_str_to_int()
    test_str_to_float()
    test_float_to_string()

if __name__ == '__main__':
    main()
