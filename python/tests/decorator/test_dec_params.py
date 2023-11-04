#!/usr/bin/python3
# 练习：python装饰器，装饰器函数本身带参数
#   装饰器：在python已有函数前后执行附加代码
#   常见类型：函数装饰器、类装饰器
# 时间：2023-11-04

import sys

# 装饰器函数本身带参数
def add_log(level='info'):
    def decorator(func):
        # 传入指定个参数：wrapper(name, age)
        def wrapper(*args):  # 传入被装饰的函数的多个参数
            # 在执行原函数前执行附加代码
            if level == 'info':  # 使用装饰器函数的参数
                print("[INFO] Enter %s" % func.__name__)
            else:
                print("[ERROR] Enter %s" % func.__name__)
            # 执行原函数，传入原函数的参数
            return func(*args)
        return wrapper
    return decorator

# 使用装饰器的函数，并给其传入参数
@add_log(level='info')
def print_name_1(name):
    print("my name is " + name)

@add_log(level='error')
def print_name_2(name):
    print("my name is " + name)

def test_dec_with_params():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # 调用函数的地方不同修改
    print_name_1("Jerry")
    print_name_2("Bob")

def main():
    test_dec_with_params()

if __name__ == '__main__':
    main()
