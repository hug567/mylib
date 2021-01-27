/*
 * 八皇后问题：在8X8格的国际象棋上摆放八个皇后（棋子），使其不能互相攻击，
 *            即任意两个皇后都不能处于同一行、同一列或同一斜线上。
 * 回溯算法：结合递归
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(fmt, ...) printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define N 8 /* 棋盘尺寸 */

int g_board[N][N] = {0}; /* 棋盘 */
int g_col[N] = {0}; /* 每行皇后所在列 */

void print_board(int size)
{
    int i, j;
    printf("board:\n");
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%d ", g_board[i][i]);
        }
        printf("\n");
    }
}

int can_set(int row, int col)
{
    int i, j;

    /* 同一横线是否有皇后 */
    for (j = 0; j < N; j++) {
        if (g_board[row][j] == 1) {
            return 0;
        }
    }

    /* 同一竖线是否有皇后 */
    for (i = 0; i < N; i++) {
        if (g_board[i][col] == 1) {
            return 0;
        }
    }

    /* 左上斜线是否有皇后 */
    for(i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (g_board[i][j] == 1) {
            return 0;
        }
    }

    /* 左下斜线是否有皇后 */
    for(i = row, j = col; i < N && j >= 0; i++, j--) {
        if (g_board[i][j] == 1) {
            return 0;
        }
    }

    /* 右上斜线是否有皇后 */
    for(i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (g_board[i][j] == 1) {
            return 0;
        }
    }

    /* 右下斜线是否有皇后 */
    for(i = row, j = col; i < N && j < N; i++, j++) {
        if (g_board[i][j] == 1) {
            return 0;
        }
    }

    return 1;
}

/* 清除指定行的皇后, 用于回溯 */
void clear_row(int row)
{
    int i;
    for (i = 0; i < N; i++) {
        g_board[row][i] = 0;
    }
}

/* 指定行皇后移动至下一列 */
void move_to_next_col(int row, int size)
{
    int i;
    for (i = 0; i < size - 1; i++) {
        if (g_board[row][i] = 1) {
            g_board[row][i] = 0;
            g_board[row][i + 1] = 1;
            return;
        }
    }
}

/* size: 棋盘大小 */
void search(int size)
{
    int i;
    int cur = 0; /* 当前遍历的行 */

    g_col[0] = 0;  /* 初始调试，第一个皇后放在顶点处 */
    g_board[0][0] = 1;
    while (cur < size) {
        cur++;
        for (i = 0; i < size; i++) {
            if (can_set(cur, i)) {
                g_col[cur] = i;
                g_board[cur][i] = 1;
                break;
            }
        }
        if (i < size) { /* 可以放置，遍历下一个皇后 */
            continue;
        } else {
            //clear_row(cur);
            cur--;
            g_board[cur][g_col[cur]] = 0;
            g_col[cur]++;
            if (g_col[cur] >= size) {
                printf("search failed\n");
                return;
            }
            g_board[cur][g_col[cur]] = 1;
            //move_to_next_col(cur, size);
        }
    }
}

int g_count = 0;
/* 结合递归的回溯搜索 */
void search2(int row)
{
    int i;
    if (row == 8) {
        return;
    }
//log("g_count = %d\n", g_count);
g_count++;
    for (i = 0; i < 8; i++) {
        if (can_set(row, i)) {
            g_col[row] = i;
            g_board[row][i] = 1;
            if (row == 7) {
                print_board(8);
                g_col[row] = 0;
                g_board[row][g_col[row]] = 0;
                return;
            }
        }
        search2(row + 1);
        g_col[row] = 0;  /* 回溯 */
        g_board[row][g_col[row]] = 0;
    }
}

int main(void)
{
    /* 可放置皇后 */
    printf("cat set(1, 1) = %d(1)\n", can_set(1, 1));

    /* 同一横线有皇后 */
    g_board[1][2] = 1;
    printf("cat set(1, 5) = %d(0)\n", can_set(1, 5));
    g_board[1][2] = 0;

    /* 同一竖线有皇后 */
    g_board[1][2] = 1;
    printf("cat set(4, 2) = %d(0)\n", can_set(4, 2));
    g_board[1][2] = 0;

    /* 左上竖线有皇后 */
    g_board[1][1] = 1;
    printf("cat set(4, 4) = %d(0)\n", can_set(4, 4));
    g_board[1][1] = 0;

    /* 左下竖线有皇后 */
    g_board[0][7] = 1;
    printf("cat set(7, 0) = %d(0)\n", can_set(7, 0));
    g_board[0][7] = 0;

    /* 右上竖线有皇后 */
    g_board[7][0] = 1;
    printf("cat set(0, 7) = %d(0)\n", can_set(0, 7));
    g_board[7][0] = 0;

    /* 右下竖线有皇后 */
    g_board[7][7] = 1;
    printf("cat set(3, 3) = %d(0)\n", can_set(3, 3));
    g_board[7][7] = 0;

    /* 可放置皇后 */
    g_board[1][1] = 1;
    printf("cat set(0, 4) = %d(1)\n", can_set(0, 4));
    g_board[1][1] = 0;

    search2(0);
    //print_board(N);

    return 0;
}
