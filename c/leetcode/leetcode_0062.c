/*
 * leetcode 62: 不同路径 [中等]
 * 动态规划：
 *    f(m,0) = f(0,n) = 1
 *    f(m,n) = f(m-1,n) + f(m,n-1)
 * 2022-01-20
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
#define MAX_COL_SIZE 100
int uniquePaths(int m, int n)
{
    int i, j;
    int pre[MAX_COL_SIZE] = {0};
    int cur[MAX_COL_SIZE] = {0};

    for (i = 0; i < n; i++) {
        pre[i] = 1;
    }
    for (i = 1; i < m; i++) {
        cur[0] = 1;
        pre[0] = 1;
        for (j = 1; j < n; j++) {
            cur[j] = cur[j - 1] + pre[j];
            pre[j] = cur[j];  //算出当前位置路径数后，更新到pre中
        }
    }
    return pre[n - 1];
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    Log("paths: %d(28)\n", uniquePaths(3, 7));
    Log("paths: %d(3)\n", uniquePaths(3, 2));
    Log("paths: %d(28)\n", uniquePaths(7, 3));
    Log("paths: %d(6)\n", uniquePaths(3, 3));
    Log("paths: %d(1)\n", uniquePaths(1, 2));
    return 0;
}