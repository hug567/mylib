/* 无向图，边带权，邻接表 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT (int)((~0U) >> 1) /* 最大整数 */
#define MIN_INT (int)(1 << (8 * sizeof(int) - 1)) /* 最小整数 */
#define MAX_VEX 100 /* 支持的最大顶点值 */

/* 弧 */
typedef struct _arc {
	int weight; /* 权 */
	int adj_idx; /* 邻接点在顶点数组中的下标 */
	struct _arc *next; /* 指向连接在同一顶点的下一个弧 */
} Arc;

/* 顶点 */
typedef struct _vex {
	int vex; /* 顶点值 */
	struct _arc *first_arc; /* 指向第一个弧 */
} Vex;

/* 无向图，边带权，邻接表 */
typedef struct _graph {
	struct _vex vexs[MAX_VEX]; /* 顶点数组 */
	int num_vex; /* 顶点数 */
	int num_arc; /* 弧数 */
} Graph;

void graph_init(Graph *g)
{
	if (g == NULL) {
		return;
	}

	int i;
	for (i = 0; i < MAX_VEX; i++) {
		g->vexs[i].vex = MIN_INT;
		g->vexs[i].first_arc = NULL;
	}
	g->num_vex = 0;
	g->num_arc = 0;
}

/* 顶点已存在则返回下标，顶点不存在则返回最近的空节点下标 */
static int get_vex_index(Graph *g, int v)
{
	if (g == NULL) {
		return -1;
	}

	int i;
	for (i = 0; i < MAX_VEX; i++) {
		if (g->vexs[i].vex == v) {
//printf("[%s]: num_vex 1 = %d\n", __func__, g->num_vex);
			return i;
		} else if (g->vexs[i].vex == MIN_INT) {
//printf("[%s]: num_vex 2 = %d\n", __func__, g->num_vex);
			g->vexs[i].vex = v;
			g->num_vex++;
//printf("[%s]: i = %d\n", __func__, i);
			return i;
		}
	}
//printf("[%s]: i = %d\n", __func__, i);
	return -1;  /* 顶点数超过MAX_VEX */
}

/* 根据顶点下标添加弧 */
static void add_arc(Graph *g, int idx, int adj_idx, int weight)
{
	if (g == NULL) {
		return;
	}

	if (g->vexs[idx].first_arc == NULL) {
		g->vexs[idx].first_arc = (struct _arc *)malloc(sizeof(struct _arc));
		g->vexs[idx].first_arc->weight = weight;
		g->vexs[idx].first_arc->adj_idx = adj_idx;
		g->vexs[idx].first_arc->next = NULL;
	} else {
		struct _arc *arc = g->vexs[idx].first_arc;
		while (arc->next != NULL) {
			arc = arc->next;
		}
		struct _arc *new_arc = (struct _arc *)malloc(sizeof(struct _arc));
		new_arc->weight = weight;
		new_arc->adj_idx = adj_idx;
		new_arc->next = NULL;
		arc->next = new_arc;
	}
}

/* 假设每一次添加的均是新弧，不重复添加弧 */
void graph_add_arc(Graph *g, int v1, int v2, int weight)
{
	if (g == NULL) {
		return;
	}

	int idx1 = get_vex_index(g, v1);
	int idx2 = get_vex_index(g, v2);
//printf("v1 = %d, v2 = %d\n", v1, v2);
//printf("idx1 = %d, idx2 = %d\n", idx1, idx2);

	if (idx1 < 0 || idx2 < 0 || idx1 == idx2) {
		return;
	}
	add_arc(g, idx1, idx2, weight);
	add_arc(g, idx2, idx1, weight);
	g->num_arc++;
}

void graph_print(Graph *g)
{
	if (g == NULL) {
		return;
	}

	int i;
	struct _arc *arc = NULL;

	printf("num_vex = %d\n", g->num_vex);
	printf("num_arc = %d\n", g->num_arc);
	for (i = 0; i < g->num_vex; i++) {
		printf("%d(%d): ", i, g->vexs[i].vex);
		arc = g->vexs[i].first_arc;
		while (arc != NULL) {
			printf("%d/%d ", arc->adj_idx, arc->weight);
			arc = arc->next;
		}
		printf("\n");
	}
}

int main()
{
	Graph *g = (Graph *)malloc(sizeof(Graph));

	graph_init(g);
	graph_add_arc(g, 100, 101, 111);
	graph_add_arc(g, 101, 102, 222);
	graph_add_arc(g, 102, 103, 333);
	graph_add_arc(g, 103, 104, 444);
	graph_add_arc(g, 104, 100, 555);
	graph_print(g);

	free(g);
	return 0;
}
