#!/usr/bin/python3
################################################################################
# python练习：字典
# python版本：python 3.6.9
# 时间：2021-11-18
################################################################################
import sys

def test_dict_base():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # 定义字典
    person = {'name' : 'bob', 'age' : 18, 'gender' : 'male'}
    print(person)
    print(person['name'])
    print(person['age'])
    print(person['gender'])
    # 字典第一个键和值
    for key, val in person.items():
        first_key = key
        first_val = val
        break
    print("dict first key:", first_key, ", first value:", first_val)

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

# 字典中是否存在指定键值
def test_key_exist():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    stu = {'name':'Tom', 'age':18}

    if 'name' in stu:
        print("name:", stu['name'])

    if 'height' not in stu:
        print("no height in stu:", stu)

# 字典排序
def test_dict_sort():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # 按值对字典排序
    stu = {}
    stu['Tom'] = 80
    stu['Jerry'] = 90
    stu['Bob'] = 70
    stu['Alice'] = 85
    print(stu)
    # 升序
    sorted_val_up = dict(sorted(stu.items(), key=lambda x:x[1]))
    print(sorted_val_up)
    # 降序
    sorted_val_down = dict(sorted(stu.items(), key=lambda x:x[1], reverse=True))
    print(sorted_val_down)

    # 按键对字典排序
    sorted_key_up = dict(sorted(stu.items(), key=lambda x:x[0]))
    print(sorted_key_up)
    sorted_key_down = dict(sorted(stu.items(), key=lambda x:x[0], reverse=True))
    print(sorted_key_down)

def main():
    test_dict_base()
    test_key_exist()
    test_dict_sort()

if __name__ == '__main__':
    main()
