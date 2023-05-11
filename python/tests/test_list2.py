#!/usr/bin/python3
################################################################################
# python练习：单链表
# python版本：python 3.6.9
# 时间：2021-12-04
################################################################################
import sys

# 单链表类
class LNode():
    def __init__(self, elem=0):
        self.elem = elem
        self.next = None

    def print(self):
        print("list[", self.length(), "]: ", sep='', end='')
        while self is not None:
            print(self.elem, " ", sep='', end='')
            self = self.next
        print('')

    def length(self):
        len = 0
        while self is not None:
            len = len + 1
            self = self.next
        return len

    def insert_tail(self, elem):
        new = LNode(elem)
        while self.next is not None:
            self = self.next
        self.next = new

    def insert_head(self, elem):
        new = LNode(elem)
        new.next = self
        self = new
        return self

    def insert_index(self, index, elem):
        new = LNode(elem)
        i = 0
        while self.next is not None and i < index :
            self = self.next
            i = i + 1
        new.next = self.next
        self.next = new

def main():
    l = LNode(0)
    l.print()
    for num in range(1, 5):
        l.insert_tail(num)
    l.print()
    for num in range(6, 10):
        l = l.insert_head(num)
    l.print()
    l.insert_index(0, 10)
    l.insert_index(2, 11)
    l.insert_index(100, 12)
    l.print()

if __name__ == '__main__':
    main()
