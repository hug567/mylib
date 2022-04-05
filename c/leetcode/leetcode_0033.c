/*
 * leetcode 33: 搜索旋转排序数组 [中等]
 * 思路：找到旋转点，对前后两个升序数组分别做二分查找
 * 2022-04-03
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int NumIndex(int *nums, int size, int target)
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
    idx = NumIndex(nums, firstSize, target);
    if (idx >= 0) {
        return idx;
    }
    if (second == 0) {
        return -1;
    }
    idx = NumIndex(nums + second, numsSize - second, target);
    if (idx >= 0) {
        return idx + second;
    }
    return -1;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int num[] = { 4,5,6,7,0,1,2 };
    int size = ARRAY_SIZE(num);
    int target = 0;
    Log("index = %d(4)\n", search(num, size, target));
}

void TestCase2(void)
{
    int num[] = { 4,5,6,7,0,1,2 };
    int size = ARRAY_SIZE(num);
    int target = 3;
    Log("index = %d(-1)\n", search(num, size, target));
}

void TestCase3(void)
{
    int num[] = { 1 };
    int size = ARRAY_SIZE(num);
    int target = 0;
    Log("index = %d(-1)\n", search(num, size, target));
}

void TestCase4(void)
{
    int num[] = { 1 };
    int size = ARRAY_SIZE(num);
    int target = 1;
    Log("index = %d(0)\n", search(num, size, target));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    return 0;
}