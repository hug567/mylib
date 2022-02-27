/*
 * leetcode 27: 移除元素 [简单]
 * 思路：双指针
 * 2022-02-27
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int removeElement(int* nums, int numsSize, int val)
{
    int *left = nums, *right = nums;
    while (right < nums + numsSize) {
        if (*right != val) {
            *left = *right;
            left++;
        }
        right++;
    }
    return left - nums;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int num[] = { 3, 2, 2, 3 };
    int size = ARRAY_SIZE(num);
    int val = 3;
    int left = removeElement(num, size, val);
    PrintArray(num, left);
}

void TestCase2(void)
{
    int num[] = { 0, 1, 2, 2, 3, 0, 4, 2 };
    int size = ARRAY_SIZE(num);
    int val = 2;
    int left = removeElement(num, size, val);
    PrintArray(num, left);
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}

