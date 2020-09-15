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

static void InitQueue(struct Queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->num = 0;
}

static void EnQueue(struct Queue *q, int val)
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

static int DeQueue(struct Queue *q)
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

static void PrintQueue(struct Queue *q)
{
    struct QueueNode *qn = q->head;
    printf("queue: ");
    while (qn != NULL) {
        printf("%d ", qn->val);
        qn = qn->next;
    }
    printf("\n");
}

static void InitGraph(struct Graph *g)
{
    int i;

    for (i = 0; i < MAX_VEX; i++) {
        g->vexs[i].val = 0;
        g->vexs[i].first = NULL;
    }
    g->numVex = 0;
    g->numArc = 0;
}

/* 查找顶点是否存在，存在则返回在顶点数组中的下标，不存在则返回-1 */
static int VexIndex(struct Graph *g, int vex)
{
    int i;

    for (i = 0; i < g->numVex; i++) {
        if (vex == g->vexs[i].val) {
            return i;
        }
    }
    return -1;
}

/* 添加新的顶点到顶点数组中 */
static int AddVex(struct Graph *g, int vex)
{
    int index = g->numVex;
    if (g->numVex >= MAX_VEX) {
        return -1;
    }
    g->vexs[index].val = vex;
    g->numVex++;
    return index;
}

/*
 * 获取顶点下标
 * 1）、若顶点已存在，返回在顶点数组中的下标
 * 2）、若顶点不存在，插入顶点并返回在顶点数组中的下标
 */
static int GetVexIndex(struct Graph *g, int vex)
{
    int index;

    index = VexIndex(g, vex);
    if (index < 0) {
        return AddVex(g, vex);
    }
    return index;
}

static void CreateGraphByArray(struct Graph *g, int **arr_t, int size)
{
    int i;
    int m, n;
    int (*arr)[3] = (int(*)[3])arr_t;
    struct ArcNode *arc = NULL;
    struct ArcNode *temp = NULL;

    for (i = 0; i < size; i++) {
        m = GetVexIndex(g, arr[i][0]);
        n = GetVexIndex(g, arr[i][1]);
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

static void DeleteArc(struct Graph *g, int start, int end)
{
    int m, n;

    m = VexIndex(g, start); /* 起点在顶点数组中的下标 */
    n = VexIndex(g, end); /* 终点在顶点数组中的下标 */
    if (m < 0 || n < 0 || m == n) {
        return;
    }
}

static void DeleteVex(struct Graph *g, int vex)
{}

static void PrintGraph(struct Graph *g)
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

static int g_visited[MAX_VEX] = {0};
/* DFS */
static void DFS(struct Graph *g, int i)
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

static void DFSTraverse(struct Graph *g)
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
static void BFSTraverse(struct Graph *g)
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

/*
 * 判断有向图是否有环：
 * 方法一：拓扑排序
 * 1、计算图中所有点的入度，删除所有入度为0的定点；
 * 2、持续第一步直至图为空或无入度为0的定点；
 * 3、若图不为空，则表示有环；图为空，表示无环；
 */
int HasCircleTopo(struct Graph *g)
{
    int i;
}

/*
 * 判断有向图是否有环：
 * 方法二：DFS
 * visited标志含义：
 *   0: 节点未被访问过
 *   -1: 后代节点都已被访问过
 *   1: 后代节点正在被访问，又访问到该节点，表示有环
 */
static int g_hasCircleDFSFlag = 0;
static void CircleDFS(struct Graph *g, int i)
{
    struct ArcNode *arc = NULL;

    g_visited[i] = 1;
    arc = g->vexs[i].first;
    while (arc != NULL) {
        /* 弧的邻接点未被访问过 */
        if (g_visited[arc->adjIndex] == 0) {
            CircleDFS(g, arc->adjIndex);
        /* 后代节点正在被访问，又访问到该节点，表示有环 */
        } else if (g_visited[arc->adjIndex] == 1) {
            g_hasCircleDFSFlag = 1;
        }
        arc = arc->next;
    }
    /* 后代节点被访问完 */
    g_visited[i] = -1;
}

int HasCircleDFS(struct Graph *g)
{
    int i;

    for (i = 0; i < g->numVex; i++) {
        g_visited[i] = 0;
    }
    for (i = 0; i < g->numVex; i++) {
        if (g_visited[i] == 0) {
            CircleDFS(g, i);
        }
    }

    return g_hasCircleDFSFlag;
}

int main(void)
{
    int i;
    int arr[][3] = {{0, 1, 9}, {1, 2, 3}, {2, 0, 2}, {2, 3, 5}, {3, 4, 1}, {0, 4, 6}};
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

    /* DFS检测是否有环 */
    printf("graph has circle: %d\n", HasCircleDFS(&g));

    return 0;
}
