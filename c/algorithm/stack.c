/* 栈 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
	int data[MAX_SIZE];
	int top;
} sq_stack;

int is_full(sq_stack *stack)
{
	if (stack->top >= MAX_SIZE) {
		return 1;
	}
	return 0;
}

int is_empty(sq_stack *stack)
{
	if (stack->top == 0) {
		return 1;
	}
	return 0;
}

void push(sq_stack *stack, int data)
{
	if (is_full(stack)) {
		printf("stack is full!\n");
		return;
	}
	stack->data[stack->top] = data;
	stack->top++;
}

int pop(sq_stack *stack)
{
	if (is_empty(stack)) {
		printf("stack is empty!\n");
		return -1;
	}
	stack->top--;
	return stack->data[stack->top];
}

int main()
{
	int i;
	int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

	sq_stack stack = {.top = 0,};
	for (i = 0; i < 10; i++) {
		push(&stack, nums[i]);
	}
	printf("stack: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", pop(&stack));
	}
	printf("\n");
	return 0;
}
