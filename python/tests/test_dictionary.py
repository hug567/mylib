#!/usr/bin/python3
################################################################################
# python练习：字典
# python版本：python 3.6.9
# 时间：2021-11-18
################################################################################
import sys

# 定义字典
person = {'name' : 'bob', 'age' : 18, 'gender' : 'male'}
print(person)
print(person['name'])
print(person['age'])
print(person['gender'])

# 添加键值对
person['birthday'] = '2021-11-19'
print(person)

# 定义空字典
animal = {}
animal['category'] = 'dog'
print(animal)

# 修改字典中值
person['age'] = 20
print(person['name'], "\'s age: ", person['age'], sep='')

# 删除键值对
del person['birthday']
print(person)

# 遍历字典
for key, value in person.items():
    print("key: ", key, ", value: ", value, sep='')

# 遍历字典中的所有键
for key in person.keys():
    print("key: ", key, sep='')

# 按顺序遍历字典中的所有键
for key in sorted(person.keys()):
    print("key: ", key, sep='')

# 遍历字典中的所有值
for value in person.values():
    print("value: ", value, sep='')

# 列表中存储字典
person1 = {'name' : 'john', 'age' : 25}
animal1 = {'category' : 'cat'}
creature = [person1, animal1]
print(creature)

# 字典中存储列表
list1 = [1, 2, 3, 4, 5]
list2 = ['one', 'two', 'three', 'four', 'five']
number = {'math' : list1, 'english' : list2}
print(number)

# 字典中存储字典
phone = {
    'huawei' : {
        'model' : 'p50',
        'price' : 4488
        },
    'apple' : {
        'model' : 'iphone 13',
        'price' : 6799
        }
    }
print(phone)
