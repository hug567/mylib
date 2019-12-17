/* leetcode 225: 用队列实现栈(中等) */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct l_node {
	int data;
	struct l_node *next;
} ListNode;

typedef struct q_node {
	ListNode *head;
	ListNode *tail;
	int size;
} MyQueue;

MyQueue *myQueueCreate(void)
{
	MyQueue *q = (MyQueue *)malloc(sizeof(MyQueue));
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return 0;
}

void myQueuePush(MyQueue *obj, int x) {
	if (obj == NULL) {
		return;
	}

	if (obj->head == NULL) {
		obj->head = (ListNode *)malloc(sizeof(ListNode));
		obj->head->data = x;
		obj->head->next = NULL;
		obj->tail = obj->head;
	} else {
		ListNode *l = (ListNode *)malloc(sizeof(ListNode));
		l->data = x;
		l->next = NULL;
		obj->head->next = l;
		obj->head = l;
	}
	obj->size++;
}

int myQueuePop(MyQueue *obj) {
	int data = obj->tail->data;
	ListNode *tmp = obj->tail;
	obj->tail = obj->tail->next;
	free(tmp);
	obj->size--;
	return data;
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
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
	int data = 0;

	if (obj->q1->size == 0) {
		myQueuePush(obj->q1, x);
		return;
	} else {
		while (obj->q1->size > 0) {
			data = myQueuePop(obj->q1);
			myQueuePush(obj->q2, data);
		}
		myQueuePush(obj->q1, x);
		while (obj->q2->size > 0) {
			data = myQueuePop(obj->q2);
			myQueuePush(obj->q1, data);
		}
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
