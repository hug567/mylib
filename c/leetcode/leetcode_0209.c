/*
 * leetcode 209: 长度最小的子数组 [中等]
 * 思路：1）、以每一个值为起点向后查找时候连续的值是否能和大于等于target，有则更新min；
 *      2）、若前面已算出一个min，后续搜索超过min直接结束搜索；
 *      3）、若有min=1，直接return；
 * 2022-04-16
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int minSubArrayLen(int target, int* nums, int numsSize)
{
    int i, j, sum;
    int min = numsSize + 1;

    for (i = 0; i < numsSize; i++) {
        sum = 0;
        for (j = i; j < numsSize; j++) {
            sum += nums[j];
            if (sum >= target) {
                min = min < (j - i + 1) ? min : (j - i + 1);
                break;
            } else if ((j - i + 1) > min) {
                break;
            }
        }
        if (min == 1) {
            return min;
        }
    }

    return min == numsSize + 1 ? 0 : min;
}

/***** 本体调试 ******************************************************************/
void TestCase1(void)
{
    int nums[] = { 2, 3, 1, 2, 4, 3 };
    int size = ARRAY_SIZE(nums);
    int target = 7;
    Log("min sub array len: %d(2)\n", minSubArrayLen(target, nums, size));
}

void TestCase2(void)
{
    int nums[] = { 1, 4, 4 };
    int size = ARRAY_SIZE(nums);
    int target = 4;
    Log("min sub array len: %d(1)\n", minSubArrayLen(target, nums, size));
}

void TestCase3(void)
{
    int nums[] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    int size = ARRAY_SIZE(nums);
    int target = 11;
    Log("min sub array len: %d(0)\n", minSubArrayLen(target, nums, size));
}

void TestCase4(void)
{
    int nums[] = { 1, 2, 3, 4, 5 };
    int size = ARRAY_SIZE(nums);
    int target = 11;
    Log("min sub array len: %d(3)\n", minSubArrayLen(target, nums, size));
}


int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    return 0;
}