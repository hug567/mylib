/*
 * 题目：leetcode 225: 用队列实现栈
 * 难度：简单
 * 技巧：两个队列实现栈
 * 时间：2020-03-04
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	int data;
	struct node *next;
} MyList;

typedef struct {
	MyList *head;
	MyList *tail;
	int size;
} MyQueue;

MyQueue *myQueueCreate()
{
	MyQueue *q = (MyQueue *)malloc(sizeof(MyQueue));
	q->size = 0;
	q->head = NULL;
	q->tail = NULL;
	return q;
}

int myQueueEmpty(MyQueue *q)
{
	if (q  == NULL || q->size <= 0) {
		return 1;
	} else {
		return 0;
	}
}

void myQueuePush(MyQueue *q, int data)
{
	if (q == NULL) {
		printf("queue is NULL\n");
		return;
	}
	if (q->size <= 0 || q->head == NULL) {
		q->head = (MyList *)malloc(sizeof(MyList));
		q->head->data = data;
		q->head->next = NULL;
		q->tail = q->head;
		q->size = 1;
	} else {
		MyList *l = (MyList *)malloc(sizeof(MyList));
		l->data = data;
		l->next = NULL;
		q->head->next = l;
		q->head = l;
		q->size++;
	}
}

int myQueuePop(MyQueue *q)
{
	if (myQueueEmpty(q)) {
		printf("queue is empty\n");
		return (int)(1U<<(8 * sizeof(int) - 1));
	}

	MyList *l = q->tail;
	int data = l->data;
	q->tail = q->tail->next;
	q->size--;
	free(l);
	return data;
}

void myQueueFree(MyQueue *q)
{
	if (q == NULL || q->head == NULL) {
		return;
	}
	MyList *tmp = q->tail;
	while (tmp != NULL) {
		printf("free tmp\n");
		q->tail = q->tail->next;
		free(tmp);
		tmp = q->tail;
	}
	free(q);
	q = NULL;
}

typedef struct {
	MyQueue *q1;
	MyQueue *q2;
} MyStack;

/** Initialize your data structure here. */
MyStack* myStackCreate() {
	MyStack *obj = (MyStack *)malloc(sizeof(MyStack));
	obj->q1 = myQueueCreate();
	obj->q2 = myQueueCreate();
	return obj;
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
	if (obj == NULL || obj->q1 == NULL || obj->q1->size <= 0) {
		printf("stack is empty\n");
		return true;
	} else {
		return false;
	}
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
	if (obj == NULL || obj->q1 == NULL || obj->q2 == NULL) {
		return;
	}

	int tmp;
	if (obj->q1->size <= 0) {
		myQueuePush(obj->q1, x);
	} else {
		while (!myQueueEmpty(obj->q1)) {
			tmp = myQueuePop(obj->q1);
			myQueuePush(obj->q2, tmp);
		}
		myQueuePush(obj->q1, x);
		while (!myQueueEmpty(obj->q2)) {
			tmp = myQueuePop(obj->q2);
			myQueuePush(obj->q1, tmp);
		}
	}
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
	if (myStackEmpty(obj)) {
		return (int)(1L << (8 * sizeof(int) - 1));
	} else {
		return myQueuePop(obj->q1);
	}
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
	if (myStackEmpty(obj)) {
		return (int)(1L << (8 * sizeof(int) - 1));
	} else {
		return obj->q1->tail->data;
	}
}

void myStackFree(MyStack* obj) {
	myQueueFree(obj->q1);
	myQueueFree(obj->q2);
	free(obj);
	obj = NULL;
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);

 * int param_2 = myStackPop(obj);

 * int param_3 = myStackTop(obj);

 * bool param_4 = myStackEmpty(obj);

 * myStackFree(obj);
*/

int main()
{
	int i;
	MyStack *s = myStackCreate();
	for (i = 0; i < 10; i++) {
		myStackPush(s, i);
	}
	printf("stack: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", myStackPop(s));
	}
	printf("\n");
	return 0;
}
