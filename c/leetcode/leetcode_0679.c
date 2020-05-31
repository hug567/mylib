/*
 * 题目：leetcode 679: 24点游戏
 * 难度：困难
 * 技巧：dfs深度优先搜索
 *      任选两个数做运算得到一个新的数，再在三个数中任选两个数运算，重复操作，直到剩一个数为止
 * 时间：2020-05-06
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define LOCAL_DEBUG

bool dfs(double *nums, int n)
{
    int i, j;
    double x, y;

    if (n == 1) {
        if (fabs(nums[0] - 24.0) < 1e-6) {
            return true;
        } else {
            return false;
        }
    }
    /* 任选2个数计算出一个新值，与剩下的数做运算 */
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            x = nums[i];
            y = nums[j];
            nums[j] = nums[n - 1];
            nums[i] = x + y;
            if (dfs(nums, n-1)) {
                return true;
            }
            nums[i] = x - y;
            if (dfs(nums, n-1)) {
                return true;
            }
            nums[i] = y - x;
            if (dfs(nums, n-1)) {
                return true;
            }
            nums[i] = x * y;
            if (dfs(nums, n-1)) {
                return true;
            }
            if (fabs(y) > 1e-6) {
                nums[i] = x / y;
                if (dfs(nums, n-1)) {
                    return true;
                }
            }
            if (fabs(x) > 1e-6) {
                nums[i] = y / x;
                if (dfs(nums, n-1)) {
                    return true;
                }
            }
            /* 还原 */
            nums[i] = x;
            nums[j] = y;
        }
    }
    return false;
}

bool judgePoint24(int* nums, int numsSize){
    int i;
    double *dnums = (double *)malloc(numsSize * sizeof(double));

    for (i = 0; i < numsSize; i++) {
        dnums[i] = nums[i];
    }
    return dfs(dnums, numsSize);
}

int main(int argc, char *argv[])
{
    int nums[] = {4, 1, 8, 7};
    //int nums[] = {1, 2, 1, 2};
    //int nums[] = {1, 3, 4, 6};
    int numsSize = sizeof(nums) / sizeof(int);
    printf("can combination value 24: %d\n", judgePoint24(nums, numsSize));
    return 0;
}