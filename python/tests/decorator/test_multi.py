#!/usr/bin/python3
# 练习：使用多个装饰器
# 时间：2024-03-06

import sys

# 嵌套装饰器函数：函数作为参数被传入
def add_log1(func):
    def wrapper():
        # 在执行原函数前执行附加代码
        print("[add_log1] func: %s" % func.__name__)
        # 执行原函数
        return func()
    return wrapper

def add_log2(func):
    def wrapper():
        # 在执行原函数前执行附加代码
        print("[add_log2] func: %s" % func.__name__)
        # 执行原函数
        return func()
    return wrapper

# 使用多个装饰器的函数
@add_log1
@add_log2
def print_name():
    print("my name is Tom")

def test_multi():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # 调用函数的地方不同修改
    print_name()

def main():
    test_multi()

if __name__ == '__main__':
    main()
