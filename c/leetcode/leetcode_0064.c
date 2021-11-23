/*
 * leetcode 64: 最小路径和 [中等]
 * 动态规划：用p[i][j]表示从左上角走到(i,j)点的最小路径和，则有：
 *          p[i][j] = min(p[i-1][j], p[i][j-1]) + grid[i][j]
 * 对于初始条件：p[0][0] = grid[0][0];
 *   对于第一列：p[i][0] = p[i-1][0] + grid[i][0]
 *   对于第一行：p[0][j] = p[0][j-1] + grid[0][j]
 * 最后结构为：p[m-1][n-1]
 * 2021-11-22
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
int Min(int a, int b)
{
    return a < b ? a : b;
}

int minPathSum(int** _grid, int gridSize, int* gridColSize)
{
    int i, j;
    int m = gridSize;
    int n = gridColSize[0];
    int p[200][200];
#ifdef LOCAL_DEBUG
    int (*grid)[n] = (int (*)[n])_grid;
#else
    int **grid = _grid;
#endif

    p[0][0] = grid[0][0];
    for (i = 1; i < m; i++) {
        p[i][0] = p[i - 1][0] + grid[i][0];
    }
    for (j = 1; j < n; j++) {
        p[0][j] = p[0][j - 1] + grid[0][j];
    }
    for (i = 1; i < m; i++) {
        for (j = 1; j < n; j++) {
            p[i][j] = Min(p[i - 1][j], p[i][j - 1]) + grid[i][j];
        }
    }

    return p[m - 1][n - 1];
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    int grid[][3] = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1},
    };
    int gridSize = 3;
    int gridColSize[3] = {3, 3, 3};
    DebugLog("min: %d(7)\n", minPathSum((int **)grid, gridSize, gridColSize));

    return 0;
}
