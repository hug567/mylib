/*
 * 练习：队列库函数
 * 时间：2020-04-23
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>

typedef char ElementType;

static void QueuePrint(struct Queue *q)
{
    struct QNode *head = NULL;

    if (QueueIsEmpty(q)) {
        return;
    }
    head = q->head;
    printf("queue: ");
    while (head != NULL) {
        printf("%c ", *(ElementType *)head->data);
        head = head->next;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int i;
    ElementType tmp;
    struct Queue *q = NULL;
    printf("hello queue\n");

    q = QueueCreate();
    for (i = 0 + 'a'; i < 10 + 'a'; i++) {
        QueuePush(q, &i, sizeof(ElementType));
    }
    QueuePrint(q);
    if (QueuePop(q, &tmp, sizeof(ElementType)) == 0) {
        printf("queue pop data = %c\n", tmp);
    }
    QueuePrint(q);
    tmp = 10 + 'a';
    QueuePush(q, &tmp, sizeof(ElementType));
    QueuePrint(q);
    return 0;
}
