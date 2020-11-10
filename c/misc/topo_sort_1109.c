/*
 * 练习：拓扑排序,有向图顶点的线性排序
 * 2020-11-09
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX 100

/* 无权重 */
struct ArcNode {
    int adjIndex; /* 弧的邻接点在顶点数组中的下标 */
    struct ArcNode *next;
};

struct VexNode {
    int val;
    struct ArcNode *first;
};

struct Graph {
    struct VexNode vexs[MAX_VEX];
    int numVex;
    int numArc;
};

void InitGraph(struct Graph *g)
{
    int i;
    if (g == NULL) {
        return;
    }
    for (i = 0; i < MAX_VEX; i++) {
        g->vexs[i].val = 0;
        g->vexs[i].first = NULL;
    }
    g->numArc = 0;
    g->numVex = 0;
}

void CreateGraphByArray(struct Graph *g, int **__arr, int size)
{
    int (*arr)[2] = (int(*)[2])__arr;
}

int main(void)
{
    int arr[][2] = {
        { 1 , 2 },
        { 1 , 3 },
        { 3 , 2 },
        { 2 , 4 },
        { 3 , 5 },
        { 5 , 4 },
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    int row = sizeof(arr) / sizeof(arr[0]);
    int col = sizeof(arr[0]) / sizeof(arr[0][0]);
    printf("row = %d, col = %d\n", row, col);
    return 0;
}
