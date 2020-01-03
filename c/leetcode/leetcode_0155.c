/* leetcode 155: 最小栈(简单) */
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
	ListNode *min;
} MinStack;

/** initialize your data structure here. */

MinStack* minStackCreate() {
	MinStack *s = (MinStack *)malloc(sizeof(MinStack));
	s->top = NULL;
	s->min = NULL;
	return s;
}

void minStackPush(MinStack* obj, int x) {
	if (obj == NULL) {
		return;
	}
	if (obj->top == NULL) {
		obj->top = (ListNode *)malloc(sizeof(ListNode));
		obj->top->data = x;
		obj->top->next = NULL;
		obj->min = (ListNode *)malloc(sizeof(ListNode));
		obj->min->data = x;
		obj->min->next = NULL;
	} else {
		ListNode *tmp = (ListNode *)malloc(sizeof(ListNode));
		tmp->data = x;
		tmp->next = obj->top;
		obj->top = tmp;
		if (x <= obj->min->data) {
			tmp = (ListNode *)malloc(sizeof(ListNode));
			tmp->data = x;
			tmp->next = obj->min;
			obj->min = tmp;
		}
	}
}

void minStackPop(MinStack* obj) {
	if (obj == NULL || obj->top == NULL) {
		return;
	}
	ListNode *tmp = obj->top;
	int x = tmp->data;
	obj->top = obj->top->next;
	free(tmp);
	if ((obj->min != NULL) && (x == obj->min->data)) {
		tmp = obj->min;
		obj->min = obj->min->next;
		free(tmp);
	}
}

int minStackTop(MinStack* obj) {
	if (obj == NULL || obj->top == NULL) {
		return (int)(1L << (8 * sizeof(int) - 1));
	}
	return obj->top->data;
}

int minStackGetMin(MinStack* obj) {
	if (obj == NULL || obj->min == NULL) {
		return (int)(1L << (8 * sizeof(int) - 1));
	}
	return obj->min->data;
}

void minStackFree(MinStack* obj) {
	if (obj == NULL) {
		return;
	}
	ListNode *tmp = obj->top;
	while (tmp != NULL) {
		obj->top = obj->top->next;
		free(tmp);
		tmp = obj->top;
	}
	tmp = obj->min;
	while (tmp != NULL) {
		obj->min = obj->min->next;
		free(tmp);
		tmp = obj->min;
	}
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, x);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/

int main(int argc, char *argv[])
{
	MinStack *s = minStackCreate();
	minStackPush(s, -2);
	minStackPush(s, 0);
	minStackPush(s, -3);
	printf("min = %d\n", minStackGetMin(s));
	minStackPop(s);
	printf("top = %d\n", minStackTop(s));
	printf("min = %d\n", minStackGetMin(s));
	return 0;
}
