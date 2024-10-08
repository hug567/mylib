#!/usr/bin/python3
# python元组
#   1、元组定义后，其中的元素不可修改
# 2024-10-08

import sys

# 定义元组
def test_define_tuple():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 定义元组
    name = ('Tom', 'Bob', 'Jerry')
    print(name)

    # 元组长度
    print('len(name):', len(name))

    # 遍历元组
    for n in name:
        print(n)

    # 通过索引访问元组
    print("name[0]:", name[0])
    # 1:3 - 访问元素1,2
    print("name[1:3]:", name[1:3])
    # 访问最后一个元素
    print("name[-1]:", name[-1])

# 元组运算
def test_operation_tuple():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 元组合并，会保留重复元素
    name1 = ('Tom', 'Bob')
    name2 = ('Bob', 'Jerry')
    name3 = name1 + name2
    print('name3:', name3)

def main():
    test_define_tuple()
    test_operation_tuple()

if __name__ == '__main__':
    main()

