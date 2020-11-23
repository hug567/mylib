/*
 * 练习：拓扑排序,有向图顶点的线性排序
 * 2020-11-09
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX 100
#define log_info(fmt, ...) printf("[%s:%d] " fmt, __func__, __LINE__, __VA_ARGS__)

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
};

/***** 调测S代码 ****************************************************************/
/* 打印二维数组 */
void PrintArray(int **__arr, int size)
{
    int i;
    int (*arr)[2] = (int(*)[2])__arr;

    printf("array: szie = %d\n", size);
    for (i = 0; i < size; i++) {
        printf("%d %d\n", arr[i][0], arr[i][1]);
    }
}

/* 打印链表 */
void PrintList(const struct ArcNode *first)
{
    printf("list: ");
    while (first != NULL) {
        printf("%d ", first->adjIndex);
        first = first->next;
    }
    printf("\n");
}

/* 打印图 */
void PrintGraph(struct Graph *g)
{
    int i;
    struct ArcNode *arc = NULL;

    printf("graph: --------------------\n");
    for (i = 0; i < g->numVex; i++) {
        printf("%d(%d): ", g->vexs[i].val, i);
        arc = g->vexs[i].first;
        while (arc != NULL) {
            printf("%d(%d) ", g->vexs[arc->adjIndex].val, arc->adjIndex);
            arc = arc->next;
        }
        printf("\n");
    }
}

/* 打印图的所有顶点 */
void PrintGraphVexs(struct Graph *g)
{
    int i;

    printf("graph vexs: ");
    for (i = 0; i < g->numVex; i++) {
        printf("%d ", g->vexs[i].val);
    }
    printf("\n");
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

void TestList(void)
{
    int i;
    struct ArcNode *arc = NULL;

    for (i = 0; i < 10; i++) {
        arc = InsertArcNode(arc, i);
    }
    PrintList(arc);

    /* 删除首节点 */
    arc = DeleteArcNode(arc, 0);
    PrintList(arc);

    /* 删除尾节点 */
    arc = DeleteArcNode(arc, 9);
    PrintList(arc);

    /* 删除中间节点 */
    arc = DeleteArcNode(arc, 5);
    PrintList(arc);

    arc = InsertArcNode(arc, 8);
    arc = InsertArcNode(arc, 9);
    arc = InsertArcNode(arc, 10);
    PrintList(arc);
    /* 删除多个节点 */
    arc = DeleteArcNode(arc, 8);
    PrintList(arc);
}

/******************************************************************************/

struct ArcNode *InsertArcNode(struct ArcNode *first, int adjIndex)
{
    struct ArcNode *tail = NULL;
    struct ArcNode *node = NULL;

    node = (struct ArcNode *)malloc(sizeof(struct ArcNode));
    node->adjIndex = adjIndex;
    node->next = NULL;
    if (first == NULL) {
        return node;
    }
    tail = first;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
    return first;
}

struct ArcNode *DeleteArcNode(struct ArcNode *first, int adjIndex)
{
    struct ArcNode *head = NULL;
    struct ArcNode *pre = NULL;
    struct ArcNode *cur = NULL;
    struct ArcNode *tmp = NULL;

    head = (struct ArcNode *)malloc(sizeof(struct ArcNode));
    head->next = first;
    pre = head;
    cur = pre->next;
    while (cur != NULL) {
        if (cur->adjIndex == adjIndex) {
            tmp = cur;
            cur = cur->next;
            pre->next = cur;
            free(tmp);
            if (pre == head) {
                head->next = cur;
            }
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
    first = head->next;
    free(head);
    return first;
}

void DestroyArcList(struct ArcNode *first)
{
    struct ArcNode *tmp = NULL;

    while (first != NULL) {
        tmp = first;
        first = first->next;
        free(tmp);
    }
}

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
    g->numVex = 0;
}

/*
 * 若顶点在图中已存在，则返回该顶点下标
 * 若顶点不存在，则存储该顶点，并返回分配的顶点下标
 */
int GetVexIndex(struct Graph *g, int val)
{
    int i;

    for (i = 0; i < g->numVex; i++) {
        if (g->vexs[i].val == val) {
            return i; /* 顶点已存在 */
        }
    }
    if (i >= MAX_VEX) {
        printf("too many vex\n");
        return -1;
    }
    g->vexs[i].val = val; /* 新增顶点 */
    g->numVex++;
    return i;
}

void CreateGraphByArray(struct Graph *g, int **__arr, int size)
{
    int i;
    int startIndex;
    int endIndex;
    int (*arr)[2] = (int(*)[2])__arr;

    for (i = 0; i < size; i++) {
        startIndex = GetVexIndex(g, arr[i][0]);
        endIndex = GetVexIndex(g, arr[i][1]);
        g->vexs[startIndex].first =
            InsertArcNode(g->vexs[startIndex].first, endIndex);
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

void UpdateVexIndex(struct Graph *g, int oldIndex)
{
    int i;
    struct ArcNode *arc = NULL;

    /* 挪动一个顶点位置后更新图，需更新图中所有顶点边的领节点下标 */
    for (i = 0; i < g->numVex; i++) {
        arc = g->vexs[i].first;
        while (arc != NULL) {
            if (arc->adjIndex == oldIndex) {
                arc->adjIndex = oldIndex - 1;
            }
            arc = arc->next;
        }
    }
}

/* 判断有向图是否有环 */
int GraphHasCycle(struct Graph *g)//, int vexIndex)
{
    int i, index;

    while ((index = NoInDegree(g)) >= 0) {
        DestroyArcList(g->vexs[index].first);
        g->vexs[index].first = NULL;
        for (i = 0; i < g->numVex; i++) {
            g->vexs[i].first = DeleteArcNode(g->vexs[i].first, index);
        }
        /* 删除一个顶点后更新图中顶点位置及下标 */
        for (i = index; i < g->numVex - 1; i++) {
            g->vexs[i].val = g->vexs[i + 1].val;
            g->vexs[i].first = g->vexs[i + 1].first;
            g->vexs[i + 1].first = NULL;
            UpdateVexIndex(g, i + 1);
        }
        g->numVex--;
    }
    if (g->numVex > 0) {
        return 1; /* 删除所有入度为0的点后，图不为空，表示有环 */
    } else {
        return 0; /* 图为空，表示无环 */
    }
}

int main(void)
{
    struct Graph g;
    int arr[][2] = { /* 有环 */
        { 1 , 2 },
        { 2 , 3 },
        { 3 , 8 },
        { 8 , 2 },
    };
    int arr1[][2] = { /* 有环 */
        { 1 , 2 },
        { 1 , 3 },
        { 3 , 2 },
        { 2 , 4 },
        { 4 , 5 },
        { 5 , 3 },
    };
    int arr2[][2] = { /* 无环 */
        { 1 , 2 },
        { 1 , 3 },
        { 3 , 2 },
        { 2 , 4 },
        { 3 , 5 },
        { 5 , 4 },
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    //int row = sizeof(arr) / sizeof(arr[0]);
    //int col = sizeof(arr[0]) / sizeof(arr[0][0]);
    //printf("row = %d, col = %d\n", row, col);
    //PrintArray((int **)arr, size);

    //TestList();

    InitGraph(&g);
    CreateGraphByArray(&g, (int **)arr, size);
    PrintGraph(&g);
    PrintInDegree(&g);
    //PrintOutDegree(&g);

    //printf("no in degree vex index: %d\n", NoInDegree(&g));
    printf("graph has cycle: %d\n", GraphHasCycle(&g));
    PrintGraph(&g);

    return 0;
}
