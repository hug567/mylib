/*
 * 队列练习：链式队列
 * 2020-09-16
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct QueueNode {
    int val;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *head; /* 队头出队 */
    struct QueueNode *tail; /* 队尾入队 */
    int len; /* 队列长度 */
};

/* 队列初始化 */
void InitQueu(struct Queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
}

/* 入队 */
void EnQueue(struct Queue *q, int val)
{
    struct QueueNode *qn = NULL;

    qn = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    qn->val = val;
    qn->next = NULL;
    if (q->len == 0) {
        q->head = qn;
        q->tail = qn;
    } else {
        q->tail->next = qn;
        q->tail = qn;
    }
    q->len++;
}

/* 出队 */
int DeQueue(struct Queue *q)
{
    int val;
    struct QueueNode *qn = NULL;

    if (q->len <= 0) {
        return -1;
    }
    qn = q->head;
    q->head = q->head->next;
    val = qn->val;
    q->len--;
    free(qn);
    return val;
}

/* 销毁队列 */
void DestroyQueue(struct Queue *q)
{
    struct QueueNode *qn = NULL;
    struct QueueNode *next = NULL;

    if (q->len <= 0) {
        return;
    }
    qn = q->head;
    while (qn->next != NULL) {
        next = qn->next;
        free(qn);
        qn = next;
    }
    free(qn);
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
}

void PrintQueue(struct Queue *q)
{
    int i;
    struct QueueNode *qn;

    qn = q->head;
    printf("queue: ");
    while (qn != NULL) {
        printf("%d ", qn->val);
        qn = qn->next;
    }
    printf("\n");
}

int main(void)
{
    int i;
    struct Queue q;

    InitQueu(&q);
    for (i = 0; i < 10; i++) {
        EnQueue(&q, i);
    }
    PrintQueue(&q);

    i = DeQueue(&q);
    printf("dequeue value: %d\n", i);
    PrintQueue(&q);

    return 0;
}