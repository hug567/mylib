/*
 * 《手写代码必备手册》 9.1 走迷宫
 * BFS配合队列
 * 2020-09-26
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "securec.h"

#define MAX_SIZE 100

struct Point {
    int x;
    int y;
    int dis; /* 距离起点的路径长度 */
};

struct QueueNode {
    struct Point *val;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *head;
    struct QueueNode *tail;
    int len;
};

struct Point *CreatePoint(int x, int y, int dis)
{
    struct Point *p = (struct Point *)malloc(sizeof(struct Point));
    p->x = x;
    p->y = y;
    p->dis = dis;
    return p;
}

void DestroyPoint(struct Point *p)
{
    if (p == NULL) {
        return;
    }
    free(p);
}

void InitQueue(struct Queue *q)
{
    if (q == NULL) {
        return;
    }
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
}

void EnQueue(struct Queue *q, struct Point *p)
{
    struct QueueNode *qn = NULL;

    if (q == NULL || p == NULL) {
        return;
    }
    qn = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    qn->val = p;
    qn->next = NULL;
    if (q->len <= 0) {
        q->head = qn;
        q->tail = qn;
        q->len = 1;
    } else {
        q->tail->next = qn;
        q->tail = qn;
        q->len++;
    }
}

struct Point *DeQueue(struct Queue *q)
{
    struct Point *p = NULL;
    struct QueueNode *qn = NULL;

    if (q == NULL || q->len <= 0) {
        return NULL;
    }
    qn = q->head;
    q->head = q->head->next;
    q->len--;
    p = qn->val;
    free(qn);
    return p;
}

/* BFS结合队列搜索 */
int PathLength(int **_maze, int m, int n)
{
    int i;
    int x, y;
    int dir[] = {0, 1, 0, -1, 0};
    int visited[MAX_SIZE][MAX_SIZE] = {0};
    int (*maze)[n] = (int(*)[n])_maze;
    struct Queue q;
    struct Point *point = NULL, *point2 = NULL;

    InitQueue(&q);
    point = CreatePoint(0, 0, 0);
    EnQueue(&q, point);
    visited[0][0] = 1;
    while (q.len > 0) {
        point = DeQueue(&q);
        if (point->x == m - 1 && point->y == n - 1) {
            return point->dis;
        }
        for (i = 0; i < 4; i++) {
            x = point->x + dir[i];
            y = point->y + dir[i + 1];
            if (x >= 0 && x < m && y >= 0 && y < n && visited[x][y] == 0 && maze[x][y] == 0) {
                visited[x][y] = 1;
                point2 = CreatePoint(x, y, point->dis + 1);
                EnQueue(&q, point2);
            }
        }
        DestroyPoint(point);
    }
    return -1;
}

int main(void)
{
    /*
     * 起点：(0, 0)
     * 终点：(4, 4)
     * 计算：起点到终点的步数
     */
    int maze[][5] = {
        { 0, 1, 0, 0, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 0 },
    };
    printf("path length = %d\n", PathLength((int **)maze, 5, 5));
    return 0;
}