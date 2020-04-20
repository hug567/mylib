/* 基本队列 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>

struct Queue *QueueCreate(void)
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
}

int QueueIsEmpty(struct Queue *q)
{
    if (q == NULL || q->len == 0) {
        return 1;
    } else {
        return 0;
    }
}

void QueuePush(struct Queue *q, void *data, size_t size)
{
    struct QNode *node = (struct QNode *)malloc(sizeof(struct QNode));
    node->data = malloc(size);
    node->next = NULL;
    memcpy(node->data, data, size);
    if (QueueIsEmpty(q)) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = q->tail->next;
    }
    q->len++;
}

int QueuePop(struct Queue *q, void *data, size_t size)
{
    struct QNode *node = NULL;

    if (QueueIsEmpty(q) || data == NULL) {
        return -1;
    } else {
        node = q->head;
        q->head = q->head->next;
        q->len--;
        memcpy(data, node->data, size);
        free(node->data);
        free(node);
        return 0;
    }
}
