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

def main():
    test_define_list()
    test_traverse_list()

if __name__ == '__main__':
    main()
