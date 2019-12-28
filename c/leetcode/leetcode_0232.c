/* leetcode 232: 用栈实现队列(简单) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	int data;
	struct node *next;
} ListNode;

typedef struct {
	ListNode *top;
} MyStack;

MyStack* myStackCreate(void)
{
	MyStack *obj = (MyStack *)malloc(sizeof(MyStack));
	obj->top = NULL;
	return obj;
}

int myStackEmpty(MyStack *obj)
{
	if (obj == NULL || obj->top == NULL) {
		printf("stack is empty\n");
		return 1;
	} else {
		return 0;
	}
}

void myStackPush(MyStack *obj, int x)
{
	if (obj == NULL) {
		return;
	}
	if (obj->top == NULL) {
		obj->top = (ListNode *)malloc(sizeof(ListNode));
		obj->top->data = x;
		obj->top->next = NULL;
	} else {
		ListNode *n = (ListNode *)malloc(sizeof(ListNode));
		n->data = x;
		n->next = obj->top;
		obj->top = n;
	}
}

int myStackPop(MyStack *obj)
{
	if (myStackEmpty(obj)) {
		return (int)(1U<<(8 * sizeof(int) - 1));
	}
	int data = obj->top->data;
	ListNode *n = obj->top;
	obj->top = obj->top->next;
	free(n);
	return data;
}

int myStackPeek(MyStack *obj)
{
	if (myStackEmpty(obj)) {
		return (int)(1U<<(8 * sizeof(int) - 1));
	}
	return obj->top->data;
}

void myStackFree(MyStack *obj)
{
	if (obj == NULL) {
		return;
	}
	ListNode *tmp = obj->top;
	while (tmp != NULL) {
		obj->top = obj->top->next;
		free(tmp);
		tmp = obj->top;
	}
	free(obj);
}

typedef struct {
	MyStack *s1;
	MyStack *s2;
} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {
	MyQueue *obj = (MyQueue *)malloc(sizeof(MyQueue));
	obj->s1 = myStackCreate();
	obj->s1->top = NULL;
	obj->s2 = myStackCreate();
	obj->s2->top = NULL;
	return obj;
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
	if (obj == NULL || obj->s1 == NULL || obj->s1->top == NULL) {
		return 1;
	} else {
		return 0;
	}
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
	if (obj == NULL || obj->s1 == NULL) {
		printf("queue is NULL\n");
		return;
	}
	myStackPush(obj->s1, x);
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	if (myQueueEmpty(obj)) {
		printf("queue is empty\n");
		return (int)(1U<<(8 * sizeof(int) - 1)); /* min int */
	}
	int tmp, x;
	while (!myStackEmpty(obj->s1)) {
		tmp = myStackPop(obj->s1);
		myStackPush(obj->s2, tmp);
	}
	x = myStackPop(obj->s2);
	while (!myStackEmpty(obj->s2)) {
		tmp = myStackPop(obj->s2);
		myStackPush(obj->s1, tmp);
	}
	return x;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {

}

void myQueueFree(MyQueue* obj) {

}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 * int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
*/

int main()
{
	int i;

	MyStack *s = myStackCreate();
	for (i = 0; i < 10; i++) {
		myStackPush(s, i);
	}
	printf("peek: %d\n", myStackPeek(s));
	printf("stack: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", myStackPop(s));
	}
	printf("\n");
	return 0;
}
