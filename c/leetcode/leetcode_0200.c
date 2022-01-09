/*
 * leetcode 200: 岛屿数量 [中等]
 * 思路：1）、找到一个陆地'1'点，以该点为起点做BFS，将与之相连的陆地均标记为'0'；
 *      2）、一次BFS可遍历完一个岛屿，岛屿数量加1；
        3）、找到下一个'1'点，继续做BFS，直至没有'1'；
 * 2022-1-9
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
bool hasIsland(char **array, int row, int col, int *x, int *y)
{
    int i, j;
#ifdef LOCAL_DEBUG
    char (*arr)[col] = (char (*)[col])array;
#else
    char **arr = array;
#endif
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (arr[i][j] == '1') {
                *x = i;
                *y = j;
                return true;
            }
        }
    }
    return false;
}

#define MAX_QUEUE_SIZE 100
int g_queue_x[MAX_QUEUE_SIZE];
int g_queue_y[MAX_QUEUE_SIZE];
int g_head, g_tail;
int numIslands(char** grid, int gridSize, int* gridColSize)
{
    int i, num = 0;
    int x, y, m, n, start_x, start_y;
    int row = gridSize, col = gridColSize[0];
    int pos[] = { 0, 1, 0, -1, 0 };
#ifdef LOCAL_DEBUG
    char (*arr)[col] = (char (*)[col])grid;
#else
    char **arr = grid;
#endif

    while (hasIsland(grid, row, col, &start_x, &start_y)) {
        num++; /* 岛屿数量+1 */
        g_head = 0;
        g_tail = 0;
        g_queue_x[g_tail] = start_x;
        g_queue_y[g_tail] = start_y;
        arr[start_x][start_y] = '0';
        g_tail++;
        while (g_head != g_tail) {
            x = g_queue_x[g_head];
            y = g_queue_y[g_head];
            g_head++;
            g_head %= MAX_QUEUE_SIZE;
            for (i = 0; i < 4; i++) {
                m = x + pos[i];
                n = y + pos[i + 1];
                if (m >= 0 && m < row && n >= 0 && n < col && arr[m][n] == '1') {
                    g_queue_x[g_tail] = m;
                    g_queue_y[g_tail] = n;
                    g_tail++;
                    g_tail %= MAX_QUEUE_SIZE;
                    arr[m][n] = '0';
                }
            }
        }
    }
    return num;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    char arr[][5] = {
        { '1', '1', '1', '1', '0' },
        { '1', '1', '0', '1', '0' },
        { '1', '1', '0', '0', '0' },
        { '0', '0', '0', '0', '0' },
    };
    int row = sizeof(arr) / sizeof(arr[0]);
    int col = sizeof(arr[0]) / sizeof(arr[0][0]);
    Log("island number: %d(1)\n", numIslands((char **)arr, row, &col));
}

void TestCase2(void)
{
    char arr[][5] = {
        { '1', '1', '0', '0', '0' },
        { '1', '1', '0', '0', '0' },
        { '0', '0', '1', '0', '0' },
        { '0', '0', '0', '1', '1' },
    };
    int row = sizeof(arr) / sizeof(arr[0]);
    int col = sizeof(arr[0]) / sizeof(arr[0][0]);
    Log("island number: %d(3)\n", numIslands((char **)arr, row, &col));
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}