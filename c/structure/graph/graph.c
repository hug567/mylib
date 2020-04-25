/* 无向图，边带权，邻接矩阵 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT (int)((~0U) >> 1)
#define MIN_INT (int)(1 << (8 * sizeof(int) - 1))
#define MAX_SIZE 100

typedef struct {
	int vexs[MAX_SIZE]; /* 顶点可能值：非负整数 */
	int arcs[MAX_SIZE][MAX_SIZE]; /* 无权边：1有，0无 */
	int num_vex;  /* 当前顶点数 */
	int num_arc; /* 当前边数 */
} MyGraph;

static int graph_vex_pos(MyGraph *g, int vex)
{
	int i = 0;
	while (g->vexs[i] != -1 && i < MAX_SIZE) {
		if (g->vexs[i] == vex) {
			return i;
		}
		i++;
	}
	if (i < MAX_SIZE) {
		g->num_vex++;
		g->vexs[i] = vex;
//printf("[vex]: i = %d\n", i);
		return i;
	} else {
		return -1;
	}
}

static void graph_init(MyGraph *g)
{
	if (g == NULL) {
		return;
	}

	int i, j;
	for (i = 0; i < MAX_SIZE; i++) {
		g->vexs[i] = -1;  /* 顶点值均初始化为-1 */
	}
	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			g->arcs[i][j] = MIN_INT; /* 无向边均初始化为0 */
		}
	}
	g->num_vex = 0;
	g->num_arc = 0;
}

static void graph_add_arc(MyGraph *g, int v1, int v2, int weight)
{
	int index1, index2;

	if (g == NULL) {
		printf("[%s][%d] g is NULL\n", __func__, __LINE__);
		return;
	}
	index1 = graph_vex_pos(g, v1);
	if (index1 < 0) {
		return;
	}
	index2 = graph_vex_pos(g, v2);
	if (index2 < 0) {
		return;
	}
//printf("index1 = %d, index2 = %d\n", index1, index2);
	if (g->arcs[index1][index2] == MIN_INT) {
		g->num_arc++;
	}
	g->arcs[index1][index2] = weight;
	g->arcs[index2][index1] = weight;
}

static void graph_print(MyGraph *g)
{
	int i, j;

	if (g == NULL) {
		return;
	}
	printf("num_vex = %d, num_arc = %d\n", g->num_vex, g->num_arc);
	printf("vex: ");
	for (i = 0; i < g->num_vex; i++) {
		printf("%4d ", g->vexs[i]);
	}
	printf("\n");
	for (i = 0; i < g->num_vex; i++) {
		printf("%3d: ", g->vexs[i]);
		for (j = 0; j < g->num_vex; j++) {
			if (g->arcs[i][j] == MIN_INT) {
				printf("  *  ");
			}
			else {
				printf("%4d ", g->arcs[i][j]);
			}
		}
		printf("\n");
	}
}

int main()
{
	MyGraph *g = (MyGraph *)malloc(sizeof(MyGraph));
	graph_init(g);
	graph_add_arc(g, 0, 1, 100);
	graph_add_arc(g, 1, 2, 101);
	graph_add_arc(g, 2, 3, 102);
	graph_add_arc(g, 3, 4, 103);
	graph_add_arc(g, 4, 0, 104);
	graph_print(g);

	free(g);
	return 0;
}
