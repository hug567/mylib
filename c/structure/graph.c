/* 无向图，边无全，邻接表 */
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

static int is_new_vex(MyGraph *g, int vex)
{
	int i = 0;
	while (g->vexs[i] != -1 && i < MAX_SIZE) {
		if (g->vexs[i] == vex) {
			return 0;
		}
		i++;
	}
	return 1;
}

static int get_vex_pos(MyGraph *g, int vex)
{
	if (is_new_vex(g, vex)) {
		return -1;
	}
	int i = 0;
	while (g->vexs[i] != -1 && i < MAX_SIZE) {
		if (g->vexs[i] == vex) {
			return i;
		}
		i++;
	}
	return -1;
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
			g->arcs[i][j] = 0; /* 无向边均初始化为0 */
		}
	}
	g->num_vex = 0;
	g->num_arc = 0;
}

static void add_arc(MyGraph *g, int v1, int v2)
{
	if (g == NULL) {
		printf("[%s][%d] g is NULL\n", __func__, __LINE__);
		return;
	}
	if (is_new_vex(g, v1)) {
	}
}

int main()
{
	printf("MAX_INT  = %d\n", MAX_INT);
	printf("MIN_INT  = %d\n", MIN_INT);
	return 0;
}
