#!/usr/bin/python3
################################################################################
# python列表
# python 3.6.9
# 2023-09-01
################################################################################

import sys
import copy

# 定义列表
def test_define_list():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 定义字符串列表
    students = ['Tom', 'Jerry', 'Bob', 'Alice']
    # 打印整个列表
    print(students)
    # 使用索引访问列表元素, 索引从0开始
    print("students[0]:", students[0])
    print("students[1]:", students[1])
    print("students[2]:", students[2])
    print("students[3]:", students[3])
    # 访问最后一个元素，索引为-1
    print("last student:", students[-1])

    # 复制列表
    name1 = ['Tom', 'Jerry', 'Bob']
    # 适用复制简单列表，若列表中元素是子列表，不会复制子列表，子列表还指向原对象
    name2 = name1[:]
    # 若name1中元素是子列表，copy.deepcopy()会将子列表同时也复制一份
    name3 = copy.deepcopy(name1)
    # 修改name1不会影响name2和name3中的值
    name1.append('Alice')
    print('name1:', name1)
    print('name2:', name2)
    print('name3:', name3)

# 遍历列表
def test_traverse_list():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    colors = ['black', 'white', 'red', 'green', 'blue']
    print("traverse 01:----------");
    for col in colors:
        print("color:", col)

    print("traverse 02:----------");
    # 获取列表长度: len(colors)
    for i in range(0, len(colors)):
        print("color:", colors[i])

# 修改、插入、删除列表成员
def test_modify_list():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    ages = [18, 25, 36, 42]
    print("ages:", ages)
    # modify member
    print("modify: ----------")
    ages[0] = 19
    print("ages:", ages)

    print("insert: ----------")
    # 添加到列表尾部
    ages.append(58)
    # 添加到列表头部
    ages.insert(0, 7)
    # insert by index, start from 0
    ages.insert(2, 22)
    print("ages:", ages)

    print("delete: ----------")
    # delete by index, start from 0
    del ages[2]
    # delete head
    del ages[0]
    # delete tail
    del ages[-1]
    print("ages:", ages)

    print("pop: ----------")
    # pop tail
    tail = ages.pop()
    print("tail:", tail)
    # pop by index, start from 0
    member = ages.pop(1)
    print("ages[1]:", member)
    print("ages:", ages)

    print("remove: ----------")
    ages = [18, 25, 36, 42]
    print("ages:", ages)
    # remove by value
    ages.remove(25)
    print("after remove by value, ages:", ages)

# 判断列表是否为空
def test_list_empty():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    name = []
    if len(name) == 0:
        print("way1: list name is empty")
    if not name:
        print("way2: list name is empty")
    if name == []:
        print("way3: list name is empty")

def main():
    test_define_list()
    test_traverse_list()
    test_modify_list()
    test_list_empty()

if __name__ == '__main__':
    main()
