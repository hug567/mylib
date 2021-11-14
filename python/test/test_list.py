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
