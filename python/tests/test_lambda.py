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

# filter()根据提供的函数对指定列表做过滤
def test_lambda_filter():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # filter函数需要提供一个过滤函数，此过滤函数可以使用lambda表达式：
    price = [33, 3, 22, 2, 11, 1]
    expensive = list(filter(lambda x: x > 10, price))
    print(f'expensive: {expensive}')

# map()根据提供的函数对指定序列做映射
def test_lambda_map():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # map()计算平方
    num = [1, 2, 3, 4, 5, 6]
    # map()返回迭代器，可用list转换为列表
    num_sqaure = list(map(lambda x: x ** 2, num))
    print(f'num square: {num_sqaure}')

    # map()实现两个列表相加
    sum = list(map(lambda x, y: x + y, [1, 3, 5], [6, 4, 2]))
    print(f'sum: {sum}')

def main():
    test_lambda()
    test_lambda_filter()
    test_lambda_map()

if __name__ == '__main__':
    main()
