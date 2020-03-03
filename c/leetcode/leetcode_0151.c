/*
 * 题目：leetcode 151: 翻转字符串里的单词
 * 难度：
 * 时间：2020-03-03
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *handle_space(char *s)
{
	int len = strlen(s);
	char *str = (char *)malloc(len + 1);
	memset(str, '\0', len + 1);

	while (*s != '\0' && *s == ' ') {
		s++;
	}
	if (*s == '\0') {
		return NULL;
	}

	char *tmp = str;
	while (*s != '\0') {
		while (*s == ' ' && *(s + 1) != '\0' && *(s + 1) == ' ') {
			s++;
		}
		*tmp = *s;
		tmp++;
		s++;
	}
	if (*str == ' ') {
		str++;
	}
	if (*(str + strlen(str) - 1) == ' ') {
		*(str + strlen(str) - 1) = '\0';
	}
	return str;
}

void reverse_one(char *s, int start, int len)
{
	char tmp;
	for (int i = start; i < len / 2; i++) {
		tmp = *(s + i);
		*(s + i) = * (s + len - i);
		*(s + len - i) = tmp;
	}
}

char *reverse_str(char *s)
{
	int start = 0;
	int end = 0;
	for (int i = 0; i < strlen(s); i++) {
		start = i;
		if (*(s + i) == ' ') {
			end = i - 1;
		}
	}
}

char * reverseWords(char * s) {
	char *str = handle_space(s);
	if (str == NULL) {
		return "";
	}
	return reverse(str);
}

int main()
{
	char *s = "  hello world!  ";

	printf("handle space: [%s]\n", handle_space(s));
	printf("reverse: %s\n", reverseWords(s));
	return 0;
}
