################################################################################
# python练习：列表
# python版本：python 3.6.9
# 时间：2021-11-14
################################################################################
import sys

# 定义列表
subjects = ["math", "english", "physics", "chemistry"]
print(subjects)
print("list length: ", len(subjects))
print("first member: " + subjects[0])
print("first member: " + subjects[0].title())
print("last member: " + subjects[-1])

# 修改元素
subjects[0] = "biology"
print(subjects)

# 添加元素
subjects.append("history")
print(subjects)

# 插入元素
subjects.insert(0, "math")
print(subjects)

# 删除元素
del subjects[1]
print(subjects)

# 删除末尾元素
subjects.pop()
print(subjects)

# 删除指定位置元素
subjects.pop(2)
print(subjects)

# 根据值删除元素, 只删除第一个指定的值
subjects.remove("english")
print(subjects)

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

# 遍历链表
for sub in subjects:
    print("subject: " + sub)

# range函数
for value in range(1, 6):
    print(value) # 1, 2, 3, 4, 5
# 创建数值列表
numbers = list(range(1, 6))
print(numbers)

# 数值列表计算
print("min(numbers) =", min(numbers))
print("max(numbers) =", max(numbers))
print("sum(numbers) =", sum(numbers))

# 列表解析：使用for循环创建列表
squares=[value ** 2 for value in range(1, 11)] # value ^ 2
print(squares)

# 列表切片
print(squares[1:4]) # 1-3的成员
print(squares[:4]) # 0-3的成员
print(squares[4:]) # 4-末尾的成员
print(squares[-3:]) # 最后3个成员

# 复制列表
squares2 = squares[:]
print(squares2)

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
