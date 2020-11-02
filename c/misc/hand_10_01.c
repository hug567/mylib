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
static int histroy[MAP_SIZE] = {0};

/* pos: 当前遍历的点，0 ~ MAP_SIZE-1  */
void dfs(int pos, int **_map)
{
    int j, c;
    int (*map)[MAP_SIZE] = (int (*)[MAP_SIZE])_map;

    /* 遍历到最后一个地点有可涂颜色，可用方案加一 */
    if (pos == MAP_SIZE) {
        g_count++;
        return;
    }

    /* 遍历当前点能否涂4种颜色(1-4) */
    for (c = 1; c <= 4; c++) {
        int can_be_colored = 1;
        for (j = 0; j < pos; j++) {
            if () {
                can_be_colored = 0; /* 没有可以涂色颜色 */
            }
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
    return 0;
}
