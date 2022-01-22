/*
 * leetcode 63: 不同路径II [中等]
 * 先BFS遍历能否到达终点，不能则路径为0
 * 动态规划：
 *    f(m,0) = f(0,n) = 1
 *    f(m,n) = f(m-1,n) + f(m,n-1)
 *    对于有障碍物的坐标，f(x,y)=0
 *    对于首行，当出现1后，该点及后续点均不可到达，路径为0
 *    对于首列，当出现1后，该点及后续点均不可到达，路径为0
 * 2022-01-20
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
#define MAX_COL_SIZE 100
#define MAX_QUEUE_SIZE 1000

int CanReachEnd(int **array, int m, int n)
{
    int i;
    int x, y, p, q;
    int head = 0, tail = 0;
    int queue_x[MAX_QUEUE_SIZE];
    int queue_y[MAX_QUEUE_SIZE];
    int dir[3] = {0, 1, 0}; //BFS只能向下或向右搜索
    int flag[MAX_COL_SIZE][MAX_COL_SIZE] = {0};
#ifdef LOCAL_DEBUG
    int (*arr)[n] = (int(*)[n])array;
#else
    int **arr = array;
#endif

    if (arr[0][0] == 0) {
        queue_x[tail] = 0;
        queue_y[tail] = 0;
        tail++;
        flag[0][0] = 1;
    }
    while (head != tail) {
        x = queue_x[head];
        y = queue_y[head];
        head++;
        head %= MAX_QUEUE_SIZE;
        if (x == m - 1 && y == n - 1) {
            return 1;
        }
        for (i = 0; i < 2; i++) {
            p = x + dir[i];
            q = y + dir[i + 1];
            if (p >= 0 && p < m && q >= 0 && q < n) {
                if (flag[p][q] != 1 && arr[p][q] == 0) {
                    queue_x[tail] = p;
                    queue_y[tail] = q;
                    tail++;
                    tail %= MAX_QUEUE_SIZE;
                }
                flag[p][q] = 1;
            }
        }
    }

    return 0;
}

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize,
                             int* obstacleGridColSize)
{
    int i, j;
    int flagRow = 0, flagCol = 0;
    int m = obstacleGridSize;
    int n = obstacleGridColSize[0];
    int pre[MAX_COL_SIZE] = {0};
    int cur[MAX_COL_SIZE] = {0};
#ifdef LOCAL_DEBUG
    int (*arr)[n] = (int(*)[n])obstacleGrid;
#else
    int **arr = obstacleGrid;
#endif

    if (!CanReachEnd(obstacleGrid, m, n)) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (arr[0][i] == 1) { //对于首行，当出现1后，该点及后续点均不可到达，路径为0
            flagRow = 1;
        }
        if (flagRow == 1) {
            pre[i] = 0;
        } else {
            pre[i] = 1;
        }
    }
    for (i = 1; i < m; i++) {
        if (arr[i][0] == 1) { //对于首列，当出现1后，该点及后续点均不可到达，路径为0
            flagCol = 1;
        }
        if (flagCol == 1) {
            cur[0] = 0;
            pre[0] = 0;
        } else {
            cur[0] = 1;
            pre[0] = 1;
        }
        for (j = 1; j < n; j++) {
            if (arr[i][j] == 1) {
                cur[j] = 0;
                pre[j] = cur[j];  //算出当前位置路径数后，更新到pre中
            } else {
                cur[j] = cur[j - 1] + pre[j];
                pre[j] = cur[j];  //算出当前位置路径数后，更新到pre中
            }
        }
    }
    return pre[n - 1];
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int arr[][3] = {
        { 0, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 0 },
    };
    int row = sizeof(arr) / sizeof(arr[0]);
    int col = sizeof(arr[0]) / sizeof(arr[0][0]);
    Log("paths: %d(2)\n", uniquePathsWithObstacles((int **)arr, row, &col));
}

void TestCase2(void)
{
    int arr[][2] = {
        { 0, 1 },
        { 0, 0 },
    };
    int row = sizeof(arr) / sizeof(arr[0]);
    int col = sizeof(arr[0]) / sizeof(arr[0][0]);
    Log("paths: %d(1)\n", uniquePathsWithObstacles((int **)arr, row, &col));
}

void TestCase3(void)
{
    int arr[][2] = {
        { 1, 0 },
    };
    int row = sizeof(arr) / sizeof(arr[0]);
    int col = sizeof(arr[0]) / sizeof(arr[0][0]);
    Log("paths: %d(0)\n", uniquePathsWithObstacles((int **)arr, row, &col));
}

void TestCase4(void)
{
    int arr[][2] = {
        { 0, 0 },
        { 1, 1 },
        { 0, 0 },
    };
    int row = sizeof(arr) / sizeof(arr[0]);
    int col = sizeof(arr[0]) / sizeof(arr[0][0]);
    Log("paths: %d(0)\n", uniquePathsWithObstacles((int **)arr, row, &col));
}

void TestCase5(void)
{
    int arr[][18] = {
        { 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1 },
        { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0 },
        { 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0 },
        { 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1 },
        { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0 },
        { 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
    };
    int row = sizeof(arr) / sizeof(arr[0]);
    int col = sizeof(arr[0]) / sizeof(arr[0][0]);
    Log("paths: %d(13594824)\n", uniquePathsWithObstacles((int **)arr, row, &col));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();
    return 0;
}