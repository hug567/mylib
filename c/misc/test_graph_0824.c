/*
 * 有向图、领接表、DFS、BFS
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX 100

struct ArcNode {
    int adjIndex; /* 弧的邻接点在顶点数组中的下标 */
    int weight;
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

    for (i = 0; i < MAX_VEX; i++) {
        g->vexs[i].val = 0;
        g->vexs[i].first = NULL;
    }
    g->numVex = 0;
    g->numArc = 0;
}

int VexIndex(struct Graph *g, int vex)
{
    int i;

    for (i = 0; i < g->numVex; i++) {
        if (vex == g->vexs[i].val) {
            return i;
        }
    }
    g->vexs[i].val = vex;
    g->numVex++;
    return i;
}

void CreateGraphByArray(struct Graph *g, int **arr_t, int size)
{
    int i;
    int m, n;
    int (*arr)[3] = (int(*)[3])arr_t;
    struct ArcNode *arc = NULL;
    struct ArcNode *temp = NULL;

    for (i = 0; i < size; i++) {
        m = VexIndex(g, arr[i][0]);
        n = VexIndex(g, arr[i][1]);
        arc = (struct ArcNode *)malloc(sizeof(struct ArcNode));
        arc->adjIndex = n;
        arc->weight = arr[i][2];
        arc->next = NULL;
        temp = g->vexs[m].first;
        if (temp == NULL) {
            g->vexs[m].first = arc;
        } else {
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = arc;
        }
        g->numArc++;
    }
}

void PrintGraph(struct Graph *g)
{
    int i;
    struct ArcNode *arc = NULL;

    for (i = 0; i < g->numVex; i++) {
        arc = g->vexs[i].first;
        printf("%d: ", g->vexs[i].val);
        while (arc != NULL) {
            printf("%d->%d ", g->vexs[i].val, g->vexs[arc->adjIndex].val);
            arc = arc->next;
        }
        printf("\n");
    }
}

int main(void)
{
    int arr[][3] = {{1, 0, 9}, {1, 2, 3}, {2, 0, 2}, {2, 3, 5}, {3, 4, 1}, {0, 4, 6}};
    int size = sizeof(arr) / 12;
    struct Graph g;

    InitGraph(&g);
    CreateGraphByArray(&g, (int **)arr, size);
    PrintGraph(&g);

    return 0;
}
