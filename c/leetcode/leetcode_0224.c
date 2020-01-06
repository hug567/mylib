/* leetcode 224: 基本计算器(困难) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 1000

typedef struct {
	long data[MAX_SIZE];
	int top;
} MyStack;

static int myStackEmpty(MyStack *s)
{
	if (s->top < 0) {
		return 1;
	}
	return 0;
}

static void myStackPush(MyStack *s, long data)
{
	s->top++;
	s->data[s->top] = data;
}

static long myStackPop(MyStack *s)
{
	long data = s->data[s->top];
	s->top--;
	return data;
}

long calculate(char * s){
	int i = 0, j = 0, flag = 0;
	long tmp = 0, ret = 0;
	char str[1000000] = "\0";
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

	char str4[] = "2147483647 + 55";
	printf("%s = %ld(2147483702)\n", str4, calculate(str4));

	char str5[] = "5+3-4-(1+2-7+(10-1+3+5+(3-0+(8-(3+(8-(10-(6-10-8-7+(0+0+7)-10+5-3-2+(9+0+(7+(2-(2-(9)-2+5+4+2+(2+9+1+5+5-8-9-2-9+1+0)-(5-(9)-(0-(7+9)+(10+(6-4+6))+0-2+(10+7+(8+(7-(8-(3)+(2)+(10-6+10-(2)-7-(2)+(3+(8))+(1-3-8)+6-(4+1)+(6))+6-(1)-(10+(4)+(8)+(5+(0))+(3-(6))-(9)-(4)+(2))))))-1)))+(9+6)+(0))))+3-(1))+(7))))))))";
	printf("%s = %ld(-35), strlen = %d\n", str5, calculate(str5), strlen(str5));
	return 0;
}
