#!/usr/bin/python3
################################################################################
# python练习：变量的定义与使用
# python版本：python 3.6.3
# 时间：2020-03-29
################################################################################
import sys

# 全局变量
g_var_int = 0
g_var_str = "hello"
g_var_none = None # python中可将空值None赋值给任何变量

def test_using_var():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # print
    print("hello python world")

    # define variable
    message = "define and align variable"
    print(message)

    # assign new value to already existing variable
    message  = "assign variable"
    print(message)

def test_using_string():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # print string
    print("This is a string")
    print('This is also a string')

    # string method
    name = "Huang xing"
    # capitalize the first letter, lowercase the rest
    print("string.title(): ", name.title())
    # convert all to uppercase
    print("string.uapper(): ", name.upper())
    # convert all to lowercase
    print("string.lower(): ", name.lower())

    first_name = "Wu"
    last_name = "Sixi"
    # string connetion
    full_name = first_name + " " + last_name
    print("string connect: ", full_name)

def test_blank_char():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # escape character
    print("Languages:\n\tPython\n\tC\n\tJavaScript")

    favorite = "python      "
    # raw string
    print("favorite: [", favorite, "]", sep='')
    # delete trailing space
    print("favorite: [", favorite.rstrip(), "]", sep='')
    sys.stdout.write("favorite: [%s]\n" % favorite.rstrip())

def test_number():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
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

# 在函数中修改全局变量
def change_global_var():
    # 先声明为全局变量
    global g_var_int
    global g_var_str
    global g_var_none

    # 修改全局变量
    g_var_int = 1
    g_var_str = "world"
    g_var_none = [1, 2, 3, 4, 5]

# python全局变量
def test_global_var():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 在函数中引用全局变量
    print("g_var_int:", g_var_int)
    print("g_var_str:", g_var_str)
    print("g_var_none:", g_var_none)

    # 修改全局变量
    change_global_var()

    # 再次引用全局变量
    print("g_var_int:", g_var_int)
    print("g_var_str:", g_var_str)
    print("g_var_none:", g_var_none)

# 一个或多个参数，至少一个
def _print_args_one_or_more(first, *left):
    print("-----------")
    print("var1:", first)
    length = len(left)
    print("left var length:", length)
    i = 2
    for var in left:
        print("var" + str(i) + ":", var)
        i = i + 1

# python可变参数
def test_func_args():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    _print_args_one_or_more(1)
    _print_args_one_or_more(2, 3)
    _print_args_one_or_more(4, 5, 6)

def main():
    test_using_var()
    test_using_string()
    test_blank_char()
    test_number()
    test_var_type()
    test_global_var()
    test_func_args()

if __name__ == '__main__':
    main()
