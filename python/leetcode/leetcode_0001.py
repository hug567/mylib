# leetcode 1: 两数之和 [简单]
# python 3.6.9
# 2022-01-23
import sys
from typing import List

##### 提交代码 ##################################################################
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        idx = [0, 0]
        for i in range(0, len(nums) - 1):
            for j in range(i + 1, len(nums)):
                if nums[i] + nums[j] == target:
                    idx[0] = i
                    idx[1] = j
                    return idx
        return idx

##### 本地调试 ##################################################################
def test_case1():
    num = [2, 7, 11, 5]
    target = 9
    s = Solution()
    idx = s.twoSum(num, target)
    print("idx: [", idx[0], ", ", idx[1], "]", sep='')

def test_case2():
    num = [3, 2, 4]
    target = 6
    s = Solution()
    idx = s.twoSum(num, target)
    print("idx: [", idx[0], ", ", idx[1], "]", sep='')

def test_case3():
    num = [3, 3]
    target = 6
    s = Solution()
    idx = s.twoSum(num, target)
    print("idx: [", idx[0], ", ", idx[1], "]", sep='')

def main():
    test_case1()
    test_case2()
    test_case3()

if __name__ == '__main__':
    main()