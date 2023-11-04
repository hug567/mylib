#!/usr/bin/python3
# 练习：python装饰器，被装饰的函数带有参数
#   装饰器：在python已有函数前后执行附加代码
#   常见类型：函数装饰器、类装饰器
# 时间：2023-11-04

import sys

# 装饰器函数：函数作为参数被传入
def add_log(func):
    # 传入指定个参数：wrapper(name, age)
    def wrapper(*args):  # 传入被装饰的函数的多个参数
        # 在执行原函数前执行附加代码
        print("Enter %s" % func.__name__)
        # 执行原函数，传入原函数的参数
        return func(*args)
    return wrapper

# 使用装饰器的函数，此函数带有参数
@add_log
def print_name(name):
    print("my name is " + name)

def test_with_params():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # 调用函数的地方不同修改
    print_name("Jerry")

def main():
    test_with_params()

if __name__ == '__main__':
    main()
