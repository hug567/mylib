#!/usr/bin/python3
################################################################################
# python练习：if语句
# python版本：python 3.6.9
# 时间：2021-11-16
################################################################################
import sys

# 真: True
# 假: False

def test_if():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    # 简单if语句
    subjects = ["math", "english"]
    for sub in subjects:
        if sub == "math": # 字符串比较相等
            print(sub.title())
        elif sub != "math": # 字符串比较不相等
            print(sub.upper())
        else:
            print("xxx")

# if语句换行
def test_if_newline():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    name = 'Tom'
    # if语句换行
    if name == 'Tom' or \
        name == 'Jerry':
        print(f'{name} is our student')
    else:
        print(f'{name} is not our student')

def main():
    test_if()
    test_if_newline()

if __name__ == '__main__':
    main()
