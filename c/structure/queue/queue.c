/*
 * 练习：链式队列库函数
 * 时间：2020-04-25
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>

/*
 * head                        tail
 * n1 -> n2 -> n3 -> .....  -> nk
 * pop from head               push to tail
 */
struct Queue *QueueCreate(void)
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
    return q;
}

void QueueDestory(struct Queue *q)
{
    struct QNode *node = NULL;

    if (q == NULL) {
        return;
    }
    while (q->head != NULL) {
        node = q->head;
        q->head = q->head->next;
        free(node);
    }
    free(q);
}

int QueueIsEmpty(struct Queue *q)
{
    if (q == NULL || q->len == 0) {
        return 1;
    } else {
        return 0;
    }
}

/* queue push to tail */
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

/* queue pop from head */
int QueuePop(struct Queue *q, void *data, size_t size)
{
    struct QNode *node = NULL;

    if (QueueIsEmpty(q)) {
        return -1;
    } else {
        node = q->head;
        q->head = q->head->next;
        q->len--;
        if (data != NULL) {
            memcpy(data, node->data, size);
        }
        free(node->data);
        free(node);
        return 0;
    }
}
