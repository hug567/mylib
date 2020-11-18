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

/* 打印每个顶点的入度 */
void PrintInDegree(struct Graph *g)
{
    int i;
    struct ArcNode *arc = NULL;
    int inDegree[MAX_VEX] = {0};

    for (i = 0; i < g->numVex; i++) {
        arc = g->vexs[i].first;
        while (arc != NULL) {
            inDegree[arc->adjIndex]++;
            arc = arc->next;
        }
    }
    printf("graph in degree:\n");
    for (i = 0; i < g->numVex; i++) {
        printf("%d: %d\n", g->vexs[i].val, inDegree[i]);
    }
}

/* 打印每个顶点的出度 */
void PrintOutDegree(struct Graph *g)
{
    int i;
    int num;
    struct ArcNode *first = NULL;

    printf("graph out degree:\n");
    for (i = 0; i < g->numVex; i++) {
        printf("%d: ", g->vexs[i].val);
        num = 0;
        first = g->vexs[i].first;
        while (first != NULL) {
            num++;
            first = first->next;
        }
        printf("%d\n", num);
    }
}

/*
 * 从图中找到一个入度为0的点，返回其在顶点数组中的下标
 * 若没有，则返回-1
 */
int NoInDegree(struct Graph *g)
{
    int i;
    struct ArcNode *arc = NULL;
    int inDegree[MAX_VEX] = {0};

    for (i = 0; i < g->numVex; i++) {
        arc = g->vexs[i].first;
        while (arc != NULL) {
            inDegree[arc->adjIndex]++;
            arc = arc->next;
        }
    }
    for (i = 0; i < g->numVex; i++) {
        if (inDegree[i] == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * 删除图中一个顶点，及与之相关的边
 */
int DeleteVex(struct Graph *g, int vexIndex)
{
    int i, index;
    struct ArcNode *arc = NULL;
    struct ArcNode *arcNext = NULL;

    if (g == NULL || vexIndex < 0) {
        return;
    }
    index = NoInDegree(g);
    if (index < 0) {
        return -1;
    }
    /* 删除入度为零的点的所有出边 */
    arc = g->vexs[index].first;
    while (arc != NULL) {
        arcNext = arc->next;
        free(arc);
        g->numArc--;
        arc = arcNext;
    }
    g->vexs[index].first = NULL;
    /* 删除入度为零的点的所有入边 */
    for (i = 0; i < g->numVex; i++) {
        arc = g->vexs[i].first;
        while (arc != NULL) {
            if (arc->adjIndex == vexIndex) {}
            arc = arc->next;
        }
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
    PrintInDegree(&g);
    PrintOutDegree(&g);

    printf("no in degree vex index: %d\n", NoInDegree(&g));

    return 0;
}
