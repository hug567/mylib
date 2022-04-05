/*
 * leetcode 34: 在排序数组中查找元素的第一个和最后一个位置 [中等]
 * 思路：二分查找，先找到是否有目标值，如果有，再查找范围
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int BinarySearch(int *nums, int size, int target)
{
    int left = 0;
    int right = size - 1;
    int mid;

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

int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
    int i, idx;
    int *ret = NULL;

    ret = malloc(2 * sizeof(int));
    ret[0] = -1;
    ret[1] = -1;
    *returnSize = 2;

    if (numsSize < 1) {
        return ret;
    }
    idx = BinarySearch(nums, numsSize, target);
    if (idx < 0) {
        return ret;
    }
    if (nums[0] == target) {
        ret[0] = 0;
    } else {
        for (i = idx - 1; i > 0; i--) {
            if (nums[i] != target) {
                break;
            }
        }
        ret[0] = i + 1;
    }
    if (nums[numsSize - 1] == target) {
        ret[1] = numsSize - 1;
    } else {
        for (i = idx + 1; i < numsSize - 1; i++) {
            if (nums[i] != target) {
                break;
            }
        }
        ret[1] = i - 1;
    }

    return ret;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int nums[] = {5,7,7,8,8,10};
    int size = ARRAY_SIZE(nums);
    int target = 8;
    int retSize;
    int *ret = searchRange(nums, size, target, &retSize);
    Log("range: [%d, %d](3, 4)\n", ret[0], ret[1]);
}

void TestCase2(void)
{
    int nums[] = {5,7,7,8,8,10};
    int size = ARRAY_SIZE(nums);
    int target = 6;
    int retSize;
    int *ret = searchRange(nums, size, target, &retSize);
    Log("range: [%d, %d](-1, -1)\n", ret[0], ret[1]);
}

void TestCase3(void)
{
    int *nums = NULL;
    int size = 0;
    int target = 0;
    int retSize;
    int *ret = searchRange(nums, size, target, &retSize);
    Log("range: [%d, %d](-1, -1)\n", ret[0], ret[1]);
}

void TestCase4(void)
{
    int nums[] = {1};
    int size = ARRAY_SIZE(nums);
    int target = 1;
    int retSize;
    int *ret = searchRange(nums, size, target, &retSize);
    Log("range: [%d, %d](0, 0)\n", ret[0], ret[1]);
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    return 0;
}
