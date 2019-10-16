/* 基本队列 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
	int data[MAX_SIZE];
	int front;
	int rear;
	int size;
} Queue;

void QueueInit(Queue *queue)
{
	queue->front = -1;
	queue->rear = -1;
	queue->size = 0;
}

void QueueIn(Queue *queue, int data)
{
	if (queue->size >= MAX_SIZE) {
		printf("queue full!");
		return;
	}
	queue->front++;
	queue->front %= MAX_SIZE;
	queue->data[queue->front] = data;
	queue->size++;
}

int QueueOut(Queue *queue)
{
	if (queue->size == 0) {
		printf("queue empty!\n");
		return -1;
	}
	queue->rear++;
	queue->rear %= MAX_SIZE;
	queue->size--;
	return queue->data[queue->rear];
}

int main()
{
	int i = 0;
	Queue *queue = (Queue *)malloc(sizeof(Queue));

	QueueInit(queue);
	for (i = 0; i < 10; i++) {
		QueueIn(queue, i);
	}
	printf("queue: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", QueueOut(queue));
	}
	printf("\n");

	return 0;
}
