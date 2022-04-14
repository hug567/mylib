/*
 * leetcode 162: 寻找峰值 [中等]
 * 思路：最大值一定是一个峰值，一遍遍历后，返回最大值对应的索引
 * 2022-04-14
 */
#include "common.h"

/****** 提交代码 *****************************************************************/
int findPeakElement(int* nums, int numsSize)
{
    int i;
    int maxIdx = 0;

    for (i = 0; i < numsSize; i++) {
        if (nums[i] > nums[maxIdx]) {
            maxIdx = i;
        }
    }
    return maxIdx;
}

/****** 本地调试 *****************************************************************/

int main(void)
{
    return 0;
}