/* 无向图，边带权，邻接表 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT (int)((~0U) >> 1) /* 最大整数 */
#define MIN_INT (int)(1 << (8 * sizeof(int) - 1)) /* 最小整数 */
#define MAX_VEX 100 /* 支持的最大顶点值 */

/* 弧 */
typedef struct _arc {
	int vex;
	int weight;
	struct _arc *next;
} Arc;

/* 顶点 */
typedef struct _vex {
	int data;
	struct _arc *first_arc;
} Vex;

/* 无向图，边带权，邻接表 */
typedef struct _graph {
	struct _vex vexs[MAX_VEX];
	int num_vex; /* 顶点数 */
	int num_arc; /* 弧数 */
} Graph;

static void graph_init(Graph *g)
{
	if (g == NULL) {
		return;
	}

	int i;
	for (i = 0; i < MAX_VEX; i++) {
		g->vexs[i].data = MIN_INT;
		g->vexs[i].first_arc = NULL;
	}
	g->num_vex = 0;
	g->num_arc = 0;
}

int main()
{
	printf("hello graph2\n");
	Graph *g = (Graph *)malloc(sizeof(Graph));

	graph_init(g);

	free(g);
	return 0;
}
