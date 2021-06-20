/*
 * leetcode 6: Z字形变换 [中等]
 * 2021-06-20
 */
#include "common.h"

void PrintCharArray(char **arr, int m, int n)
{
    int i, j;

    printf("arr:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
}

/***** 提交代码 ****************************************************************/

#define MAX_SIZE 1000

char *convert(char * s, int numRows)
{
    int x, y, i, j, col;
    char arr[MAX_SIZE][MAX_SIZE] = {0};
    int len = strlen(s);
    int dir = 0; /* 放置方向：0：竖直向下，1：向右上角 */
    char *out;

    if (numRows == 1) {
        return s;
    }

    memset(arr, 0, MAX_SIZE * MAX_SIZE);
    out = (char *)malloc(len + 1);
    memset(out, 0, len + 1);
    /* 初始坐标与方向 */
    x = 0;
    y = 0;
    dir = 0;
    for (i = 0; i < len; i++) {
        arr[x][y] = s[i];
        if (x == numRows - 1) {
            dir = 1; /* 下一个向右上方向 */
        } else if (x == 0) {
            dir = 0; /* 下一个向竖直向下方向 */
        }
        if (dir == 0) {
            x++;
        } else {
            x--;
            y++;
        }
    }

    col = len / (2 * numRows - 2) + 1;
    col = col * (numRows - 1);

    x = 0;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < col; j++) {
            if (arr[i][j] != 0) {
                out[x] = arr[i][j];
                x++;
            }
        }
    }

    return out;
}

/***** 本地调试 ****************************************************************/
int main(void)
{
    DebugLog("s = %s(PAHNAPLSIIGYIR)\n", convert("PAYPALISHIRING", 3));
    DebugLog("s = %s(PINALSIGYAHRPI)\n", convert("PAYPALISHIRING", 4));
    DebugLog("s = %s(A)\n", convert("A", 1));
    return 0;
}
