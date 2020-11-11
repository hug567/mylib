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

int GetVexIndex(struct Graph *g, int val)
{
    int i;

    for (i = 0; i < g->numVex; i++) {
        if (g->vexs[i].val == val) {
            return i; /* 顶点已存在 */
        }
    }
    if (i < MAX_VEX) {
        g->vexs[i].val = val;
        g->numVex++; /* 新增顶点 */
        return i;
    } else {
        printf("too many vex\n");
        return -1;
    }
}

void AddArch(struct Graph *g, int start, int end)
{
    int startIndex = GetVexIndex(g, start);
    struct ArcNode *first = g->vexs[startIndex].first;
    struct ArcNode *arc = (struct ArcNode *)malloc(sizeof(struct ArcNode));
    arc->adjIndex = end;
    arc->next = NULL;
    if (first == NULL) {
        g->vexs[startIndex].first = arc;
    } else {
        while (first->next != NULL) {
            first = first->next;
        }
        first->next = arc;
    }
    g->numArc++;
}

void CreateGraphByArray(struct Graph *g, int **__arr, int size)
{
    int i;
    int (*arr)[2] = (int(*)[2])__arr;

    for (i = 0; i < size; i++) {
        AddArch(g, arr[i][0], arr[i][1]);
    }
}

void PrintGraph(struct Graph *g)
{
    int i;
    struct ArcNode *arc = NULL;

    for (i = 0; i < g->numVex; i++) {
        printf("%d: ", g->vexs[i].val);
        arc = g->vexs[i].first;
        while (arc != NULL) {
            printf("%d ", arc->adjIndex);
            arc = arc->next;
        }
        printf("\n");
    }
}

int main(void)
{
    struct Graph g;
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

    InitGraph(&g);
    CreateGraphByArray(&g, (int **)arr, size);
    PrintGraph(&g);

    return 0;
}
