/*
 * 练习：队列头文件
 * 创建：2020-04-20
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

/* 链栈节点 */
struct QNode {
    void *data;
    struct QNode *next;
};

/* 链栈 */
struct Queue {
    struct QNode *head;
    struct QNode *tail;
    int len;
};

int QueueIsEmpty(struct Queue *s);
struct Queue *QueueCreate(void);
void QueueDestory(struct Queue *s);
void QueuePush(struct Queue *s, void *data, size_t size);
int QueuePop(struct Queue *s, void *data, size_t size);

#endif /* __QUEUE_H__ */
