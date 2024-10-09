#!/usr/bin/python3
# deque():
#   1、创建固定大小的队列，队列满时，再插入新元素，最老的元素将被移除
#   2、若创建时不指定大小，队列大小无限制
# 2024-10-09

import sys
from collections import deque

# 创建队列
def test_deque():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')

    q = deque(maxlen=3)
    q.append(1)
    q.append(2)
    q.append(3)
    print(q)
    # 队列已满，再插入新元素
    q.append(4)
    print(q)

    # 创建大小无限制的队列
    q2 = deque()
    q2.append('Tom')
    q2.append('Bob')
    q2.append('Jerry')
    print(q2)

def main():
    test_deque()

if __name__ == '__main__':
    main()
