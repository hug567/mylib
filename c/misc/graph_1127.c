/*
 * 练习：有向图、无权 ，顶点、边均用链表存储
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log_info(fmt, ...) printf("[INFO ][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

struct VexNode;

struct ArcNode {
    struct VexNode *adjVex;
    struct ArcNode *next;
};

/* 单向双链表连接自身，同时有入边和出边两个边链表 */
struct VexNode {
    int val;
    struct ArcNode *inArc;
    struct ArcNode *outArc;
    struct VexNode *pre;
    struct VexNode *next;
};

struct Graph {
    struct VexNode *first;
    int numVex;
};

struct ArcNode *InsertArcNode(struct ArcNode *first, struct VexNode *adjVex)
{
    struct ArcNode *arc = NULL;
    struct ArcNode *tail = NULL;

    arc = (struct ArcNode *)malloc(sizeof(struct ArcNode));
    arc->adjVex = adjVex;
    arc->next = NULL;
    if (first == NULL) {
        first = arc;
    } else {
        tail = first;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = arc;
    }
    return first;
}

struct ArcNode *DeleteArcNode(struct ArcNode *first, const struct VexNode *adjVex)
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
        if (cur->adjVex == adjVex) {
            tmp = cur;
            cur = cur->next;
            pre->next = cur;
            free(tmp);
            if (head == pre) {
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

void PrintGraph(const struct Graph *g)
{
    struct VexNode *vex = NULL;
    struct ArcNode *arc = NULL;

    vex = g->first;
    printf("graph: \n");
    while (vex != NULL) {
        printf("%d -> ", vex->val);
        arc = vex->outArc;
        while (arc != NULL) {
            printf("%d ", arc->adjVex->val);
            arc = arc->next;
        }
        printf("\n");
        printf("  <- ");
        arc = vex->inArc;
        while (arc != NULL) {
            printf("%d ", arc->adjVex->val);
            arc = arc->next;
        }
        printf("\n");
        vex = vex->next;
    }
}

void InitGraph(struct Graph *g)
{
    g->first = NULL;
    g->numVex = 0;
}

struct VexNode *GetVexNode(struct Graph *g, int val)
{
    int i;
    struct VexNode *vex = g->first;
    struct VexNode *tail = NULL;
    struct VexNode *newVex = NULL;

    while (vex != NULL) {
        if (vex->val == val) {
            return vex;
        }
        if (vex->next == NULL) {
            tail = vex;
        }
        vex = vex->next;
    }
    newVex = (struct VexNode *)malloc(sizeof(struct VexNode));
    newVex->val = val;
    newVex->inArc = NULL;
    newVex->outArc = NULL;
    newVex->pre = NULL;
    newVex->next = NULL;
    if (g->numVex <= 0) {
        g->first = newVex;
    } else {
        tail->next = newVex;
        newVex->pre = tail;
    }
    g->numVex++;
    return newVex;
}

void CreateGraphByArray(struct Graph *g, int **__arr, int size)
{
    int i;
    int (*arr)[2] = (int(*)[2])__arr;
    struct VexNode *startVex = NULL;
    struct VexNode *endVex = NULL;

    for (i = 0; i < size; i++) {
        startVex = GetVexNode(g, arr[i][0]);
        endVex = GetVexNode(g, arr[i][1]);
        startVex->outArc = InsertArcNode(startVex->outArc, endVex);
        endVex->inArc = InsertArcNode(endVex->inArc, startVex);
    }
}

struct VexNode *NoInDegree(struct Graph *g)
{
    struct VexNode *vex = g->first;

    while (vex != NULL) {
        if (vex->inArc == NULL) {
            return vex;
        }
        vex = vex->next;
    }
    return NULL;
}

void DeleteVexNode(struct Graph *g, struct VexNode *vex)
{
    struct VexNode *temp = NULL;
    struct ArcNode *arc = NULL;

    DestroyArcList(vex->outArc);
    vex->outArc = NULL;
    DestroyArcList(vex->inArc);
    vex->inArc = NULL;

    temp = g->first;
    while (temp != NULL) {
        temp->outArc = DeleteArcNode(temp->outArc, vex);
        temp->inArc = DeleteArcNode(temp->inArc, vex);
        temp = temp->next;
    }

    if (vex->pre == NULL) { /* vex是头顶点 */
        g->first = vex->next;
        if (g->first != NULL) { /* 不是最后一个顶点 */
            g->first->pre = NULL;
        }
    } else if (vex->next == NULL) { /* vex是尾顶点 */
        vex->pre->next = NULL;
    } else { /* vex是中间顶点 */
        vex->pre->next = vex->next;
        vex->next->pre = vex->pre;
    }
    free(vex);
    g->numVex--;
}

int GraphHasCycle(struct Graph *g)
{
    struct VexNode *vex = NULL;

    while ((vex = NoInDegree(g)) != NULL) {
        DeleteVexNode(g, vex);
    }

    if (g->numVex <= 0) {
        return 0;
    } else {
        return 1;
    }
}

int main(void)
{
    int arr1[][2] = {
        { 0, 1 },
    };
    int arr[][2] = {
        { 1, 0 },
        { 0, 1 },
    };
    int arr3[][2] = {
        { 1, 2 },
        { 2, 3 },
        { 3, 8 },
        { 8, 1 },
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    struct Graph g;

    InitGraph(&g);
    CreateGraphByArray(&g, (int **)arr, size);
    PrintGraph(&g);

    struct VexNode *vex = NoInDegree(&g);
    if (vex != NULL) {
        printf("no in degree vex: %d\n", vex->val);
    }
    printf("graph has cycle: %d\n", GraphHasCycle(&g));
    PrintGraph(&g);

    return 0;
}
