#!/usr/bin/python3
################################################################################
# python练习：列表
# python版本：python 3.6.9
# 时间：2021-11-14
################################################################################
import sys

def test_define_list():
    print(sys._getframe().f_code.co_name, ": ---------------------------------")
    # 定义列表
    subjects = ["math", "english", "physics", "chemistry"]
    print(subjects)
    print("list length: ", len(subjects))
    print("first member: " + subjects[0])
    print("first member: " + subjects[0].title())
    print("last member: " + subjects[-1])

    # 列表解析：使用for循环创建列表
    squares=[value ** 2 for value in range(1, 11)] # value ^ 2
    print("squares:", squares)
    #print(squares)

    # 复制列表
    squares2 = squares[:]
    print("squares2", squares2)

def test_modify_list():
    print(sys._getframe().f_code.co_name, ": ---------------------------------")
    subjects = ["math", "english", "physics", "chemistry"]

    # 修改元素
    subjects[0] = "biology"
    print("modify:", subjects)

    # 添加元素
    subjects.append("history")
    print("append:", subjects)

    # 插入元素
    subjects.insert(0, "math")
    print("insert [0]:", subjects)

    # 删除元素
    del subjects[1]
    print("delete:", subjects)

    # 删除末尾元素
    subjects.pop()
    print("delete tail:", subjects)

    # 删除指定位置元素
    subjects.pop(2)
    print("delete [2]:", subjects)

    # 根据值删除元素, 只删除第一个指定的值
    subjects.remove("english")
    print("delete first matched value:", subjects)

    # 列表切片
    nums = list(range(1, 6))
    print("nums[1:4]", nums[1:4]) # 1-3的成员
    print("nums[:4]", nums[:4]) # 0-3的成员
    print("nums[4:]", nums[4:]) # 4-末尾的成员
    print("nums[-3:]", nums[-3:]) # 最后3个成员

def test_sort_list():
    print(sys._getframe().f_code.co_name, ": ---------------------------------")
    subjects = ["math", "english", "physics", "chemistry"]

    subjects.append("english")
    subjects.append("physics")
    # 排序列表
    subjects.sort()
    print(subjects)

    # 倒序
    subjects.sort(reverse=True)
    print(subjects)

    # 临时排序
    print(sorted(subjects))
    print(subjects)

    # 反转列表元素
    subjects.reverse()
    print(subjects)

def test_traverse_list():
    print(sys._getframe().f_code.co_name, ": ---------------------------------")
    subjects = ["math", "english", "physics", "chemistry"]

    # 遍历列表
    for sub in subjects:
        print("subject: " + sub)

    # 列表元素个数
    print("subject length: ", len(subjects), sep='')

    # 遍历列表
    for i in range(0, len(subjects)):
        print("subjects[", i, "] = ", subjects[i], sep='')

    # range函数
    for value in range(1, 6):
        print(value) # 1, 2, 3, 4, 5

def test_number_list():
    # 创建数值列表
    numbers = list(range(1, 6))
    print(numbers)

    # 数值列表计算
    print("min(numbers) =", min(numbers))
    print("max(numbers) =", max(numbers))
    print("sum(numbers) =", sum(numbers))

def test_define_tuple():
    print(sys._getframe().f_code.co_name, ": ---------------------------------")

    # 元组：值不可变的列表
    size = (10, 50, 47)
    print("size[0] :", size[0])
    print("size[1] :", size[1])
    print("size[2] :", size[2])

    # 遍历元组
    for s in size:
        print("size :", s)

    # 重新复制元组
    size = (20, 30, 62)
    print(size)

def main():
    test_define_list()
    test_modify_list()
    test_sort_list()
    test_traverse_list()
    test_define_tuple()

if __name__ == '__main__':
    main()
