/*
 * 练习：单链表队列，尾部入队，头部出队
 * 2020-11-27
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct QueueNode {
    int val;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *head;
    struct QueueNode *tail;
    int len;
};

void PrintQueue(const struct Queue *q)
{
    int i;
    struct QueueNode *node = NULL;

    node = q->head;
    printf("queue: ");
    for (i = 0; i < q->len; i++) {
        if (node == NULL) {
            break;
        }
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

void InitQueue(struct Queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
}

void EnQueue(struct Queue *q, int val)
{
    struct QueueNode *node = NULL;

    node = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    node->val = val;
    node->next = NULL;
    if (q->len == 0) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
    q->len++;
}

int DeQueue(struct Queue *q)
{
    int val;
    struct QueueNode *node = NULL;

    if (q->len <= 0) {
        return -1;
    }
    node = q->head;
    q->head = q->head->next;
    q->len--;
    if (q->len <= 0) {
        q->head = NULL;
        q->tail = NULL;
    }
    val = node->val;
    free(node);
    return val;
}

void DestroyQueue(struct Queue *q)
{
    int i;
    struct QueueNode *node = NULL;
    struct QueueNode *tmp = NULL;

    node = q->head;
    for (i = 0; i < q->len; i++) {
        if (node == NULL) {
            break;
        }
        tmp = node;
        node = node->next;
        free(tmp);
    }
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
}

int main(void)
{
    int i;
    struct Queue q;

    InitQueue(&q);
    for (i = 0; i < 10; i++) {
        EnQueue(&q, i);
    }
    PrintQueue(&q);

    for (i = 0; i < 5; i++) {
        printf("de queue: %d\n", DeQueue(&q));
    }

    for (i = 10; i < 15; i++) {
        EnQueue(&q, i);
    }
    PrintQueue(&q);

    DestroyQueue(&q);
    PrintQueue(&q);

    return 0;
}
