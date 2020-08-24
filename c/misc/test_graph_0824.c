/*
 * 有向图、领接表
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
    g->numVex = 0;
    g->numArc = 0;
}

int main(void)
{
    return 0;
}
