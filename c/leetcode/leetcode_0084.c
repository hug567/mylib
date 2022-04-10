/*
 * leetcode 84: 搜索旋转排序数组 II [中等]
 * 思路：1、qsort排序后做二分查找；
 *      2、找到旋转点，先判断在哪个单调数组中，再对其做二分查找；
 * 2022-04-09
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
int BinarySearch(int *nums, int size, int target)
{
    int left = 0, right = size - 1, mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

int search(int* nums, int numsSize, int target)
{
    int i, idx, second = 0;
    int firstSize;

    for (i = 0; i < numsSize - 1; i++) {
        if (nums[i] > nums[i + 1]) {
            second = i + 1;
            break;
        }
    }
    firstSize = (second > 0) ? second : numsSize;
    idx = BinarySearch(nums, firstSize, target);
    if (idx >= 0) {
        return idx;
    }
    if (second == 0) {
        return -1;
    }
    idx = BinarySearch(nums + second, numsSize - second, target);
    if (idx >= 0) {
        return idx + second;
    }
    return -1;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int nums[] = {};
    int size = ARRAY_SIZE(nums);
}

int main(void)
{
    return 0;
}