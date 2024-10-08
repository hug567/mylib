#!/usr/bin/python3
# python解压序列赋值给多个变量
# 2024-10-08

import sys

# 解压赋值
def test_decompress_assign():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 元组分解赋值
    p = (4, 5)
    x, y = p
    print('x:', x)
    print('y:', y)

    # 列表中有多种类型值，分解赋值
    stu = ['Tom', 18, (2006, 10, 12)]
    name, age, birth = stu
    print('name:', name)
    print('age:', age)
    print('birth:', birth)
    # 子元素也可以分解赋值
    name, age, (year, mon, day) = stu
    print('year:', year)
    print('mon:', mon)
    print('day:', day)

    # 分解字符串为单个字符
    word = 'Hello'
    a, b, c, d, e = word
    print('a:', a)
    print('b:', b)
    print('c:', c)
    print('d:', d)
    print('e:', e)

def test_decompress_part():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 分解后只保留一部分，丢弃不关心的值
    stu = ['Bob', 19, (2005, 9, 21)]
    _, age, _ = stu
    print('age:', age)

    # 星号表达式获取分解后的多个值
    grades = [100, 99, 98, 97, 96, 95]
    first, *middle, last = grades
    print('first:', first)
    print('middle:', middle)
    print('last:', last)

    # 星号表达式在尾部获取0个或多个数据
    member1 = ['Tom', 25]
    name, age, *phone = member1
    print('name:', name)
    print('age:', age)
    print('phone:', phone)

    member2 = ['Bob', 25, 18212345678]
    name, age, *phone = member2
    print('name:', name)
    print('age:', age)
    print('phone:', phone)

    # 星号表达式丢弃部分元素
    name, *_ = member2
    print('name:', name)

def main():
    test_decompress_assign()
    test_decompress_part()

if __name__ == '__main__':
    main()
