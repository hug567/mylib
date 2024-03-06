#!/usr/bin/python3
# 练习：python装饰器嵌套
# 时间：2024-03-06

import sys

# 嵌套装饰器函数：函数作为参数被传入
def add_log1(func0):
    def wrapper1(func1):
        def wrapper2():
            # 在执行原函数前执行附加代码
            print("[add_log1] func0: %s" % func0.__name__)
            print("[add_log1] func1: %s" % func1.__name__)
            return func0(func1)()
        return wrapper2
    return wrapper1

@add_log1
def add_log2(func):
    def wrapper():
        # 在执行原函数前执行附加代码
        print("[add_log2] func: %s" % func.__name__)
        # 执行原函数
        return func()
    return wrapper

# 使用装饰器的函数
@add_log2
def print_name():
    print("my name is Tom")

def test_nest():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # 调用函数的地方不同修改
    print_name()

def main():
    test_nest()

if __name__ == '__main__':
    main()
