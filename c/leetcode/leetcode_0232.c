/* leetcode 232: 用栈实现队列(简单) */
#include <stdio.h>
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
		n->next = obj->top->next;
		obj->top->next = n;
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

void myStackFree(MyStack *boj)
{
	if (obj == NULL) {
		return;
	}
}

typedef struct {

} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {

}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {

}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {

}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {

}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {

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
	return 0;
}
