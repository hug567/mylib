/*
 * 练习：无向图，邻接矩阵
 * 2020-08-16
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_NUM 65535

struct Graph {
    int vex[MAX_SIZE];
    int arc[MAX_SIZE][MAX_SIZE];
    int numVex;
    int numArc;
};

void InitGraph(struct Graph *g)
{
    int i, j;
    for (i = 0; i < MAX_SIZE; i++) {
        g->vex[i] = MAX_NUM;
        for (j = 0; j < MAX_SIZE; j++) {
            g->arc[i][j] = MAX_NUM;
        }
    }
    g->numVex = 0;
    g->numArc = 0;
}

int main(void)
{
    return 0;
}