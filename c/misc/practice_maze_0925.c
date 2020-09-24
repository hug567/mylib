/*
 * 走迷宫：BFS
 * 2020-09-25
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pos {
    int x;
    int y;
    int dis;
};

struct QueueNode {
    struct Pos *p;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *head;
    struct QueueNode *tail;
    int len;
};

void EnQueue(struct Queue *q, struct Pos *p)
{
    struct QueueNode *qn = NULL;

    qn = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    qn->p = p;
    qn->next = NULL;
    if (q->len <= 0) {
        q->head = qn;
        q->tail = qn;
    } else {
        q->tail->next = qn;
        q->tail = qn;
    }
    q->len++;
}

struct Pos *DeQueue(struct Queue *q)
{}

int BFS(int **_maze, int m, int n)
{
    return 0;
}

int main(void)
{
    int maze[][5] = {
        { 0, 1, 0, 0, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 0 }
    };
    return 0;
}