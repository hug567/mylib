/*
 * 《手写代码必备手册》 10.1 四色问题
 * 
 * 2020-10-13
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 8

static int g_count = 0; /* 方案个数 */
/* 遍历至第i个点时，前i-1个点的着色，1-4表示4种着色，0表示未着色 */
static int g_histroy[MAP_SIZE] = {0};

/* pos: 当前遍历的点，0 ~ MAP_SIZE-1  */
void dfs(int pos, int **__map)
{
    int j, c;
    int (*map)[MAP_SIZE] = (int (*)[MAP_SIZE])__map;

    /* 遍历到最后一个地点有可涂颜色，可用方案加一 */
    if (pos == MAP_SIZE) {
        g_count++;
        return;
    }

    /* 遍历当前点能否涂4种颜色(1-4) */
    for (c = 1; c <= 4; c++) {
        int can_be_colored = 1;
        for (j = 0; j < pos; j++) {
            /* 前驱点与当前点相邻，且与当前颜色相同，则不可着当前颜色 */
            if (map[pos][j] && (g_histroy[j] == c)) {
                can_be_colored = 0; /* 没有可以涂色颜色 */
            }
        }
        if (can_be_colored) { /* 当前点可着色 */
            g_histroy[pos] = c; /* 记录当前点颜色 */
            dfs(pos + 1, __map); /* 变量下一个点 */
        }
    }
}

int main(void)
{
    int map[][MAP_SIZE] = {
        { 0, 0, 0, 1, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 1, 0 },
        { 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 0 },
    };

    dfs(0, (int **)map);
    printf("count = %d\n", g_count);

    return 0;
}
