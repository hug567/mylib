/*
 * leetcode 53: 最大子序和 [简单]
 * 动态规划：使用f(i)表示第i个数结尾的连续子数组的最大和，则整个数组的连续子数组最大和为：
 *          max{f(i)};
 *          对于f(i)有：f(i) = max{f(i-1) + n(i), n(i)}, 显然有：f(0) = n(0)
 * 2021-11-09
 */

#include "common.h"

/***** 提交代码 ****************************************************************/
int max(int a, int b)
{
    return a > b ? a : b;
}

int maxSubArray(int* nums, int numsSize){
    int i;
    int maxSum = nums[0];
    int f[numsSize];

    f[0] = nums[0];
    for (i = 1; i < numsSize; i++) {
        f[i] = max(f[i - 1] + nums[i], nums[i]);
        maxSum = max(f[i], maxSum);
    }
    return maxSum;
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    int arr1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    DebugLog("maxSunArray = %d(6)\n", maxSubArray(arr1, sizeof(arr1) / sizeof(arr1[0])));
    return 0;
}
