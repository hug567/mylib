/*
 * leetcode 130: 被围绕的区域 [中等]
 * 思路：被X包围的O一定不与边界相连，则识别出与边界的O相连的O，剩下的O均是被X包围的
 *       1）、以每一个边界O为起点，做BFS，将与之相连的O改为A；
 *       2）、遍历完后，将剩下的O改为X；
 *       3）、最后将所有的A改回O；
 * 2022-1-8
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
#define MAX_QUEUE_SIZE 100
int g_queue_x[MAX_QUEUE_SIZE];
int g_queue_y[MAX_QUEUE_SIZE];
int g_head, g_tail;

void Bfs(char **array, int row, int col, int start_x, int start_y)
{
    int i;
    int x, y, m, n;
    int pos[] = {0, 1, 0, -1, 0};
#ifdef LOCAL_DEBUG
    char (*arr)[col] = (char (*)[col])array;
#else
    char **arr = array; /* leetcode */
#endif

    g_head = 0;
    g_tail = 0;
    g_queue_x[g_tail] = start_x;
    g_queue_y[g_tail] = start_y;
    g_tail++;
    arr[start_x][start_y] = 'A';
    while (g_head != g_tail) {
        x = g_queue_x[g_head];
        y = g_queue_y[g_head];
        g_head++;
        g_head %= MAX_QUEUE_SIZE;
        for (i = 0; i < 4; i++) {
            m = x + pos[i];
            n = y + pos[i + 1];
            if (m >= 0 && m < row && n >= 0 && n < col && arr[m][n] == 'O') {
                g_queue_x[g_tail] = m;
                g_queue_y[g_tail] = n;
                g_tail++;
                g_tail %= MAX_QUEUE_SIZE;
                arr[m][n] = 'A';
            }
        }
    }
}

void solve(char** board, int boardSize, int* boardColSize)
{
    int i, j;
#ifdef LOCAL_DEBUG
    char (*arr)[boardColSize[0]] = (char (*)[boardColSize[0]])board;
#else
    char **arr = board; /* leetcode */
#endif

    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardColSize[i]; j++) {
            if ((i == 0 || j == 0 || i == boardSize - 1 ||
                j == boardColSize[i] - 1) && (arr[i][j] == 'O')) {
                Bfs(board, boardSize, boardColSize[i], i, j);
            }
        }
    }
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardColSize[i]; j++) {
            if (arr[i][j] == 'O') {
                arr[i][j] = 'X';
            } else if (arr[i][j] == 'A') {
                arr[i][j] = 'O';
            }
        }
    }
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int i, j;
    char board[][4] = {
        { 'X', 'X', 'X', 'X' },
        { 'X', 'O', 'O', 'X' },
        { 'X', 'X', 'O', 'X' },
        { 'X', 'O', 'X', 'X' },
    };
    int row = 4;
    int colSize[] = { 4, 4, 4, 4 };
    solve((char **)board, row, colSize);
    Log("board:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < colSize[i]; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    TestCase1();
    return 0;
}
