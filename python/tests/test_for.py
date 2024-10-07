#!/usr/bin/python3
################################################################################
# python练习：for
# python版本：python 3.6.9
# 时间：2023-09-04
################################################################################
import sys

# list, array, string, i 0-10
# for i in range(0, 10) # 0-9

def test_for_base():
    # for循环遍历，0—9
    for i in range(0, 10):
        print("i:", i)

def main():
    test_for_base()

if __name__ == "__main__":
    main()
