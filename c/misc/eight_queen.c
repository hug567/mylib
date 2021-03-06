/*
 * 八皇后问题：在8X8格的国际象棋上摆放八个皇后（棋子），使其不能互相攻击，
 *            即任意两个皇后都不能处于同一行、同一列或同一斜线上。
 * 解法一：回溯算法，结合递归（未验证）
 * 解法二：DFS，基于递归实现
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DebugLog(fmt, ...) {if (1) {printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__);}}

#define N 8 /* 棋盘尺寸 */

int g_queue[N] = {0}; /* 每行皇后所在列 */
int g_count = 0; /* 可以的方案总数 */

void PrintBoard(void)
{
    int i, j;
    printf("board:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int val = 0;
            if (g_queue[i] == j) {
                val = 1;
            }
            printf("%d ", val);
        }
        printf("\n");
    }
}

/*
 * 当前点能否放置皇后，前0~row-1行的皇后均已放置，且每行皇后所在列
 * 存储在g_queue[N]数组中
 */
int CanSet(int row, int col)
{
    int i;

    /* 遍历每行皇后与当前点是否在同一列或同一斜线，肯定不在同一行 */
    for (i = 0; i < row; i++) {
        /*
         * 在同一列：col相同
         * 在同一斜线：行列坐标差值相同
         */
        if (g_queue[i] == col || (row - i) == (col - g_queue[i]) ||
            (row - i) == (g_queue[i] - col)) {
            return 0; /* 不可放置 */
        }
    }
    return 1; /* 可以放置 */
}

int g_flag = 1;
/* DFS: 搜索当前row行可放置皇后的位置 */
void search(int row)
{
    int i;

    if (row == N) { /* 0~N-1行均放置了皇后，为满足条件的方案 */
        g_count++;
        if (g_flag == 1) {
            PrintBoard();
            g_flag = 0;
        }
        return;
    }

    /* 遍历当前行哪个位置可放置皇后 */
    for (i = 0; i < N; i++) {
        int canSet = CanSet(row, i); /* 当前点(row, i)能否放置皇后 */
        if (canSet) { /* 可以放置 */
            g_queue[row] = i; /* 放置皇后 */
            search(row + 1); /* 搜索下一行 */
        }
    }
}

int main(void)
{

    search(0); /* 从第0行开始搜索 */
    printf("g_count = %d(92)\n", g_count);

    return 0;
}
