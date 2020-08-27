/*
 * 有向图、领接表、DFS、BFS
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX 100

struct ArcNode {
    int vex;
    int weight;
    struct ArcNode *next;
};

struct VexNode {
    int vex;
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
        g->vexs[i].vex = 0;
        g->vexs[i].first = NULL;
    }
    g->numVex = 0;
    g->numArc = 0;
}

int VexIndex(struct Graph *g, int vex)
{
    int i;

    for (i = 0; i < g->numVex; i++) {
        if (vex == g->vexs[i].vex) {
            return i;
        }
    }
    g->vexs[i].vex = vex;
    g->numVex++;
    return i;
}

void CreateGraphByArray(struct Graph *g, int **arr_t, int size)
{
    int i;
    int (*arr)[3] = (int(*)[3])arr_t;
}

void PrintGraph(struct Graph *g)
{}

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
