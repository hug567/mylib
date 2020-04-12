/* 链式队列 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct node {
	int data;
	struct node *next;
} List;

typedef struct {
	List *head;
	List *tail;
	int size;
} Queue;

Queue* QueueCreate(void)
{
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}

int QueueEmpty(Queue *q)
{
	if (q == NULL || q->size == 0) {
		return 1;
	} else {
		return 0;
	}
}

void QueueIn(Queue *q, int data)
{
	if (q->size == 0) {
		q->head = (List *)malloc(sizeof(List));
		q->head->data = data;
		q->head->next = NULL;
		q->tail = q->head;
		q->size = 1;
	} else {
		List *l = (List *)malloc(sizeof(List));
		l->data = data;
		l->next = NULL;
		q->head->next = l;
		q->head = l;
		q->size++;
	}
}

int QueueOut(Queue *q)
{
	if (QueueEmpty(q)) {
		printf("queue is empty!\n");
		return -1;
	}
	List *l = q->tail;
	q->tail = q->tail->next;
	q->size--;
	int data = l->data;
	free(l);
	return data;
}

void QueueDelete(Queue *q)
{
	List *l = q->tail;
	List *tmp = NULL;
	while (l != NULL) {
		tmp = l;
		free(tmp);
		l = l->next;
	}
	free(q);
}

int main()
{
	int i = 0;

	Queue* q = QueueCreate();
	for (i = 0; i < 10; i++) {
		QueueIn(q, i);
	}
	/*QueueDelete(q);
	q = NULL;*/
	printf("queue: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", QueueOut(q));
	}
	printf("\n");

	return 0;
}
