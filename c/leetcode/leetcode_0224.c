/* leetcode 224: 基本计算器(困难) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
	int data[MAX_SIZE];
	int top;
} MyStack;

static int myStackEmpty(MyStack *s)
{
	if (s->top < 0) {
		return 1;
	}
	return 0;
}

static void myStackPush(MyStack *s, int data)
{
	s->top++;
	s->data[s->top] = data;
}

static int myStackPop(MyStack *s)
{
	int data = s->data[s->top];
	s->top--;
	return data;
}

int calculate(char * s){
	int i = 0, j = 0, tmp = 0, ret = 0, flag = 0;
	char str[100] = "\0";
	MyStack s1 = {.data = {0}, .top = -1};
	MyStack s2 = {.data = {0}, .top = -1};

	/* 去除空格 */
	while (s[i] != '\0') {
		if (s[i] != ' ') {
			str[j] = s[i];
			j++;
		}
		i++;
	}
	/* 开始计算 */
	i = 0;
	while(str[i] != '\0') {
		if (str[i] == '(') {
			flag = 0;
			i++;
			continue;
		}
		tmp = 0;
		while (str[i] >= '0' && str[i] <= '9') {
			tmp = tmp * 10 + str[i] - '0';
			i++;
		}
		if (tmp != 0 || str[i - 1] == '0') {
			myStackPush(&s1, tmp);
		}
		if ((flag == 1) && !myStackEmpty(&s2)) {
			ret = myStackPop(&s1) * myStackPop(&s2)
			      + myStackPop(&s1);
			myStackPush(&s1, ret);
			flag = 0;
		}
		if (str[i] == '+') {
			myStackPush(&s2, 1);
			flag = 1;
		} else if (str[i] == '-') {
			flag = 1;
			myStackPush(&s2, -1);
		} else if (str[i] == ')' && !myStackEmpty(&s2)) {
			ret = myStackPop(&s1) * myStackPop(&s2)
			      + myStackPop(&s1);
			myStackPush(&s1, ret);
		}
		i++;
	}
	return myStackPop(&s1);
}

int main(int argc, char *argv[])
{
	char str1[] = "1 -0+ 1 + 0";
	printf("%s = %d(2)\n", str1, calculate(str1));

	char str2[] = "2-1 + 2";
	printf("%s = %d(3)\n", str2, calculate(str2));

	char str3[] = "(1+(4+5+2)-3)+(6+8)";
	printf("%s = %d(23)\n", str3, calculate(str3));

	return 0;
}
