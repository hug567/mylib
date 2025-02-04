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

/* 方案一 */
int Compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

bool search(int* nums, int numsSize, int target)
{
    qsort(nums, numsSize, sizeof(int), Compare);
    return BinarySearch(nums, numsSize, target) >= 0;
}

#if 0 /* 方案二 */
bool search(int* nums, int numsSize, int target)
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
        return true;
    }
    if (second == 0) {
        return false;
    }
    idx = BinarySearch(nums + second, numsSize - second, target);
    if (idx >= 0) {
        return true;
    }
    return false;
}
#endif

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int nums[] = {2,5,6,0,0,1,2};
    int size = ARRAY_SIZE(nums);
    int target = 0;
    Log("target exist: %d(1)\n", search(nums, size, target));
}

int main(void)
{
    TestCase1();
    return 0;
}