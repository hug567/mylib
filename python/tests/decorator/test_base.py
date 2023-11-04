#!/usr/bin/python3
# 练习：python装饰器
#   装饰器：在python已有函数前后执行附加代码
#   常见类型：函数装饰器、类装饰器
# 时间：2023-11-04

import sys

# 装饰器函数：函数作为参数被传入
def add_log(func):
    def wrapper():
        # 在执行原函数前执行附加代码
        print("Enter %s" % func.__name__)
        # 执行原函数
        return func()
    return wrapper

# 使用装饰器的函数
@add_log
def print_name():
    print("my name is Tom")

def test_base_decorator():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # 调用函数的地方不同修改
    print_name()

def main():
    test_base_decorator()

if __name__ == '__main__':
    main()
