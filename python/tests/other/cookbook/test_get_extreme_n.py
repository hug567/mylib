# 查找最大或最小的N个元素：heapq(堆)
# 2024-10-21

import sys
import heapq

# 查找最大或最小的n个元素
def test_extreme_num():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    nums = [1, 8, 2, 23, 7, -4, 18, 23, 42, 37, 2]

    # 使用堆获取最大的3个数字
    max_n = heapq.nlargest(3, nums)
    print(f'max_n: {max_n}')

    # 使用堆获取最小的4个数字
    min_n = heapq.nsmallest(3, nums)
    print(f'min_n: {min_n}')

def main():
    test_extreme_num()

if __name__ == '__main__':
    main()