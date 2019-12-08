/* leetcode 225: 用队列实现栈(中等) */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct q_node {
	int data;
	struct q_node *next;
} MyQueue;

void myQueuePush(MyQueue *obj, int x) {
	MyQueue *q = (MyQueue *)malloc(sizeof(MyQueue));
	q->data = x;
	q->next = NULL;
	MyQueue *tmp = obj;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = q;
}

int myQueuePop(MyQueue *obj) {
	int data = obj->data;
	MyQueue *tmp = obj;
	obj = obj->next;
	free(tmp);
	return data;
}

typedef struct {
	MyQueue *q1;
	MyQueue *q2;
} MyStack;

/** Initialize your data structure here. */

MyStack* myStackCreate() {
	MyStack *obj = (MyStack *)malloc(sizeof(MyStack));
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
	if (obj->q1 == NULL) {
		obj->q1 = (MyQueue *)malloc(sizeof(MyQueue));
		obj->q1->data = x;
		obj->q1->next = NULL;
		return;
	}
	int data = 0;
	while (obj->q1 != NULL) {
		obj->q1 = obj->q1->next;
		data = myQueuePop(obj->q1);
		myQueuePush(obj->q1, data);
	}
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
}

void myStackFree(MyStack* obj) {
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
	return 0;
}
