#!/usr/bin/python3
################################################################################
# python练习：变量的定义与使用
# python版本：python 3.6.3
# 时间：2020-03-29
################################################################################
import sys

# print
print("hello python world")

# define variable
message = "define and align variable"
print(message)

# assign variable
message="assign variable"
print(message)

# string
print("This is a string")
print('This is also a string')

# string method
name = "Huang xing"
print("string.title(): ", name.title())
print("string.uapper(): ", name.upper())
print("string.lower(): ", name.lower())

# string connet
first_name = "Wu"
last_name = "Sixi"
full_name = first_name + " " + last_name
print("string connect: ", full_name)

# escape character
print("Languages:\n\tPython\n\tC\n\tJavaScript")

# delete trailing space
favorite = "python      "
print("favorite: ", favorite, ".")
print("favorite: ", favorite.rstrip(), ".")
sys.stdout.write("favorite: %s.\n" % favorite.rstrip())

# 整数加减乘除
print("2 + 3 = ", 2 + 3)  # 5
print("2 - 3 = ", 2 - 3)  # -1
print("2 * 3 = ", 2 * 3)  # 6
print("2 / 3 = ", 2 / 3)  # 0.666666...
print("2 ** 3 = ", 2 ** 3)  # 2^3 = 8

# 浮点数加减乘除
print("0.1 + 0.2 = ", 0.1 + 0.2)  # 0.30000000000000004
print("0.1 - 0.2 = ", 0.1 - 0.2)  # -0.1
print("0.1 * 0.2 = ", 0.1 * 0.2)  # 0.020000000000000004
print("0.1 / 0.2 = ", 0.1 / 0.2)  # 0.5

# 数组转字符串
print("str(1234) = " + str(1234))

def test_var_type():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    var=1
    print("var type:", type(var))
    var='12345'
    print("var type:", type(var))

def main():
    test_var_type()

if __name__ == '__main__':
    main()
