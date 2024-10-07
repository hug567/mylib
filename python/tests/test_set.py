#!/usr/bin/python3
# python集合
# 2024-10-07

import sys

# 定义集合
def test_def_set():
    print(sys._getframe().f_code.co_name, ":----------------------------------")

    # 定义数字集合
    age = {18, 21, 19, 23}
    print(age)

    # 定义字符串集合
    name = {'Tom', 'Jerry', 'Bob', 'Alice'}
    print(name)
    # 获取集合长度
    name_len = len(name)
    print('name_len:', name_len)

    # 创建空集合
    price = set()
    print(price)

# 修改集合
def test_change_set():
    print(sys._getframe().f_code.co_name, ":----------------------------------")

    name = {'Tom', 'Jerry', 'Bob', 'Alice'}
    # 遍历集合
    for n in name:
        print(n)

    # 集合添加元素
    name.add('New')
    print(name)

    # 添加多个元素到集合中，update可添加集合、列表、元组等可迭代对象
    name.update({'One', 'Two', 'Three'})
    print(name)

    # 集合移除元素
    name.remove('New')
    print(name)

    # 清空集合
    name.clear()
    print(name)

# 集合运算
def test_operation_set():
    print(sys._getframe().f_code.co_name, ":----------------------------------")

    # 合并集合，同时去除重复元素
    name1 = {'Tom', 'Jerry'}
    name2 = {'Bob', 'Tom'}
    name3 = name1 | name2;
    print(name3)
    # 使用update合并集合，同时去除重复元素
    name4 = name1
    name4.update(name2)
    print(name4)

    # 元素交集 &
    # 元素差集(相减) -

# 集合元素判断
def test_judge_set():
    print(sys._getframe().f_code.co_name, ":----------------------------------")

    # 元素是否在集合中

    # 元素是否不在集合中

def main():
    test_def_set()
    test_change_set()
    test_operation_set()
    test_judge_set()

if __name__ == '__main__':
    main()
