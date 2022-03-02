/*
 * leetcode 283: 移动零 [简单]
 * 思路：双指针
 * 2022-03-02
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
void moveZeroes(int* nums, int numsSize)
{
    int i;
    int *cur = nums;
    int *next = nums;

    for (i = 0; i < numsSize; i++) {
        if (*next != 0) {
            *cur = *next;
            cur++;
        }
        next++;
    }
    if (cur < next) {
        memset(cur, 0, (numsSize - (cur - nums)) * sizeof(int));
    }
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int nums[] = { 0, 1, 0, 3, 12 };
    int size = ARRAY_SIZE(nums);
    moveZeroes(nums, size);
    PrintArray(nums, size);
}

void TestCase2(void)
{
    int nums[] = { 0 };
    int size = ARRAY_SIZE(nums);
    moveZeroes(nums, size);
    PrintArray(nums, size);
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}
