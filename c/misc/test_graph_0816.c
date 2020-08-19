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

int VexIndex(struct Graph *g, int vex)
{
    int i;
    for (i = 0; i < g->numVex; i++) {
        if (g->vex[i] == vex) {
            return i;
        }
    }
    g->vex[i] = vex;
    g->numVex++;
    return i;
}

void CreateGraphByArray(struct Graph *g, int **arr_t, int size)
{
    int i;
    int m, n;
    int (*arr)[3] = (int(*)[3])arr_t;
    for (i = 0; i < size; i++) {
        m = VexIndex(g, arr[i][0]);
        n = VexIndex(g, arr[i][1]);
        if (g->arc[m][n] >= MAX_NUM) {
            g->numArc++;
        }
        g->arc[m][n] = arr[i][2];
        g->arc[n][m] = arr[i][2];
    }
}

void PrintGraph(struct Graph *g)
{
    int i, j;
    printf("vex: ");
    for (i = 0; i < g->numVex; i++) {
        printf("%d ", g->vex[i]);
    }
    printf("\n");
    for (i = 0; i < g->numVex; i++) {
        printf(" %d   ", g->vex[i]);
        for (j = 0; j < g->numVex; j++) {
            if (g->arc[i][j] >= MAX_NUM) {
                printf("%d ", 0);
            } else {
                printf("%d ", g->arc[i][j]);
            }
        }
        printf("\n");
    }
}

int main(void)
{
    int arr[][3] = {{0, 1, 9}, {4, 0, 6}, {1, 2, 3}, {2, 3, 5}, {3, 4, 1}, {0, 2, 2}};
    int size = sizeof(arr) / 12;
    struct Graph g;

    InitGraph(&g);
    CreateGraphByArray(&g, (int **)arr, size);
    PrintGraph(&g);

    return 0;
}
