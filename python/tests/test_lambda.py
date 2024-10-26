# python lambda表达式
# 定义：匿名函数(函数没有名字)，只包含一个语句，接受多个参数
# 2024-10-26

import sys

# lambda的简单使用
def test_lambda():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # lambda实现数值加1
    num = (lambda x: x + 1)(1)
    print(f'num: {num}')
    # 将lambda赋值给变量，然后将该变量当作函数调用
    add = lambda x: x + 1

    # lambda实现两数相乘
    num = (lambda x, y: x * y)(5, 6)
    print(f'num: {num}')

def test_lambda_filter():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # filter函数需要提供一个过滤函数，此过滤函数可以使用lambda表达式：
    price = [33, 3, 22, 2, 11, 1]
    expensive = list(filter(lambda x: x > 10, price))
    print(f'expensive: {expensive}')

def main():
    test_lambda()
    test_lambda_filter()

if __name__ == '__main__':
    main()
