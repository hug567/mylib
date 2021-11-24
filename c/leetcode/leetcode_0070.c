/*
 * leetcode 70: 爬楼梯 [简单]
 * 解法：动态规划
 * 设：用f(n)表示爬到d第n及台阶的方法，由于一次能走1步或2步，因此上到第n级台阶有2种方法，
 *    从第n-1级台阶爬1级，或从第n-2级台阶爬2级，则有：f(n) = f(n-1) + f(n-2)
 *    初始条件为：f(0) = 1, f(1) = 2
 * 2021-11-24
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
int climbStairs(int n)
{
    int i, f[100];
    f[0] = 1;
    f[1] = 2;
    for (i = 2; i < n; i++) {
        f[i] = f[i-1] + f[i-2];
    }
    return f[n-1];
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    DebugLog("climbStatrs(2) = %d(2)\n", climbStairs(2));
    DebugLog("climbStatrs(3) = %d(3)\n", climbStairs(3));
    DebugLog("climbStatrs(10) = %d(89)\n", climbStairs(10));
    return 0;
}
