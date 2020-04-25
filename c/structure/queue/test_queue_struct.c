/*
 * 练习：栈库函数
 * 时间：2020-04-12
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>

typedef struct {
    int num;
    char ch;
} ElementType;

static void QueuePrint(struct Queue *q)
{
    struct QNode *head = NULL;
    ElementType *data;

    if (QueueIsEmpty(q)) {
        return;
    }
    head = q->head;
    printf("queue: \n");
    while (head != NULL) {
        data = (ElementType *)head->data;
        printf("    num = %d, ch = %c\n", data->num, data->ch);
        head = head->next;
    }
}

int main(int argc, char *argv[])
{
    int i;
    ElementType tmp;
    struct Queue *q = NULL;
    printf("hello queue\n");

    /* 创建队列 */
    q = QueueCreate();
    /* 入队 */
    for (i = 0; i < 10; i++) {
        tmp.num = i;
        tmp.ch = i + 'a';
        QueuePush(q, &tmp, sizeof(ElementType));
    }
    /* 队列打印 */
    QueuePrint(q);

    /* 出队 */
    if (QueuePop(q, &tmp, sizeof(ElementType)) == 0) {
        printf("stack pop, num = %d, ch = %c\n", tmp.num, tmp.ch);
    }
    QueuePrint(q);

    /* 入队 */
    tmp.num = 10;
    tmp.ch = 10 + 'a';
    QueuePush(q, &tmp, sizeof(ElementType));
    QueuePrint(q);

    /* 出队 */
    QueuePop(q, NULL, 0);
    QueuePrint(q);

    /* 销毁队列 */
    QueueDestory(q);

    return 0;
}
