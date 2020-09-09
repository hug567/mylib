/*
 * 有向图、领接表、DFS、BFS
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX 100

/* 链式队列节点 */
struct QueueNode {
    int val;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *head; /* 出队头结点 */
    struct QueueNode *tail; /* 入队尾结点 */
    int num; /* 节点数量 */
};


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

void InitQueue(struct Queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->num = 0;
}

void EnQueue(struct Queue *q, int val)
{
    struct QueueNode *qn = NULL;

    qn = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    qn->val = val;
    qn->next = NULL;

    if (q->num <= 0) {
        q->head = qn;
        q->tail = qn;
    } else {
        q->tail->next = qn;
        q->tail = qn;
    }
    q->num++;
}

int DeQueue(struct Queue *q)
{
    int val;
    struct QueueNode *qn = NULL;

    if (q == NULL || q->num <= 0) {
        printf("queue is empty\n");
        return -1;
    }
    qn = q->head;
    q->head = q->head->next;
    q->num--;
    val = qn->val;
    free(qn);
    return val;
}

void PrintQueue(struct Queue *q)
{
    struct QueueNode *qn = q->head;
    printf("queue: ");
    while (qn != NULL) {
        printf("%d ", qn->val);
        qn = qn->next;
    }
    printf("\n");
}

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

int g_visited[MAX_VEX] = {0};
/* DFS */
void DFS(struct Graph *g, int i)
{
    struct ArcNode *arc = NULL;

    g_visited[i] = 1;
    printf("%d ", g->vexs[i].val);
    arc = g->vexs[i].first;
    while (arc != NULL) {
        if (!g_visited[arc->adjIndex]) {
            DFS(g, arc->adjIndex);
        }
        arc = arc->next;
    }
}

void DFSTraverse(struct Graph *g)
{
    int i;

    for (i = 0; i < g->numVex; i++) {
        g_visited[i] = 0;
    }
    for (i = 0; i < g->numVex; i++) {
        if (!g_visited[i]) {
            DFS(g, i);
        }
    }
}

/* BFS：需要使用队列 */
void BFSTraverse(struct Graph *g)
{
    int i;
    int index;
    struct ArcNode *arc = NULL;
    struct Queue q;

    InitQueue(&q);
    for (i = 0; i < g->numVex; i++) {
        g_visited[i] = 0;
    }
    for (i = 0; i < g->numVex; i++) {
        if (g_visited[i]) {
            continue;
        }
        g_visited[i] = 1;
        printf("%d ", g->vexs[i].val);
        EnQueue(&q, i);
        while (q.num > 0) {
            index = DeQueue(&q);
            arc = g->vexs[index].first;
            while (arc != NULL) {
                if (!g_visited[arc->adjIndex]) {
                    g_visited[arc->adjIndex] = 1;
                    printf("%d ", g->vexs[arc->adjIndex].val);
                    EnQueue(&q, arc->adjIndex);
                }
                arc = arc->next;
            }
        }
    }
}

int main(void)
{
    int i;
    int arr[][3] = {{1, 0, 9}, {1, 2, 3}, {2, 0, 2}, {2, 3, 5}, {3, 4, 1}, {0, 4, 6}};
    int size = sizeof(arr) / 12;
    struct Graph g;
    struct Queue q;

    InitGraph(&g);
    CreateGraphByArray(&g, (int **)arr, size);
    PrintGraph(&g);

    /* 队列测试： */
    InitQueue(&q);
    for (i = 0; i < 10; i++) {
        EnQueue(&q, i);
    }
    PrintQueue(&q);
    DeQueue(&q);
    PrintQueue(&q);

    /* DFS */
    printf("dfs: ");
    DFSTraverse(&g);
    printf("\n");

    /* BFS */
    printf("bfs: ");
    BFSTraverse(&g);
    printf("\n");

    return 0;
}
