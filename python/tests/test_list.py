#!/usr/bin/python3
################################################################################
# learinig list
# python 3.6.9
# 2023-09-01
################################################################################

import sys

def test_define_list():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    # define list
    students = ['Tom', 'Jerry', 'Bob', 'Alice']
    # print whole list
    print(students)
    # access list member, index start from 0
    print("students[0]:", students[0])
    print("students[1]:", students[1])
    print("students[2]:", students[2])
    print("students[3]:", students[3])
    # access the last student with index -1
    print("last student:", students[-1])

def test_traverse_list():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    colors = ['black', 'white', 'red', 'green', 'blue']
    print("traverse 01:----------");
    for col in colors:
        print("color:", col)

    print("traverse 02:----------");
    # list length: len(colors)
    for i in range(0, len(colors)):
        print("color:", colors[i])

# modify, insert and delete list member
def test_modify_list():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    ages = [18, 25, 36, 42]
    print("ages:", ages)
    # modify member
    print("modify: ----------")
    ages[0] = 19
    print("ages:", ages)

    print("insert: ----------")
    # insert to tail
    ages.append(58)
    # insert to head
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

    print("delete: ----------")
    print("ages:", ages)

def main():
    test_define_list()
    test_traverse_list()
    test_modify_list()

if __name__ == '__main__':
    main()
