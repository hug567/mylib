/*
 * 题目：leetcode 151: 翻转字符串里的单词
 * 难度：中等
 * 时间：2020-03-03
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse_one(char *str, int start, int len)
{
	int i;
	char tmp;

	for (i = 0; i < len / 2; i++) {
		tmp = *(str + start + i);
		*(str + start + i) = *(str + start + len - i - 1);
		*(str + start + len - i - 1) = tmp;
	}
	return str;
}

char *handle_space(char *str)
{
	int len = strlen(str);
	char *str2 = (char *)malloc(len + 1);
	char *tmp = str2;

	memset(str2, '\0', len + 1);
	while (*str != '\0') {
		if ((*str != ' ') || (*str == ' ' && *str != '\0' && *(str + 1)  != ' ')) {
			*tmp = *str;
			tmp++;
		}
		str++;
	}
	if (*str2 == ' ') {
		str2++;
	}
	if (*(str2 + strlen(str2) - 1) == ' ') {
		*(str2 + strlen(str2) - 1) = '\0';
	}

	return str2;
}

char *reverseWords(char *s)
{
	if (*s == '\0') {
		return "";
	}
	int i;
	int flag = 0;
	int len = 0;
	int start = 0;

	char *str = handle_space(s);

	str = reverse_one(str, 0, strlen(str));
	for (i = 0; i < strlen(str); i++) {
		if (flag == 1) {
			start = i;
			flag = 0;
		}
		if (str[i] != ' ' && str[i + 1] != '\0') {
			len++;
		} else {
			if (str[i + 1] == '\0') {
				len++;
			}
			str = reverse_one(str, start, len);
			flag = 1;
			len = 0;
		}
	}

	return str;
}

int main()
{
	printf("reverse: [%s]\n", reverseWords(""));
	printf("reverse: [%s]\n", reverseWords("  "));
	printf("reverse: [%s]\n", reverseWords("h"));
	printf("reverse: [%s]\n", reverseWords("hello"));
	printf("reverse: [%s]\n", reverseWords(" hello"));
	printf("reverse: [%s]\n", reverseWords("hello "));
	printf("reverse: [%s]\n", reverseWords("  hello"));
	printf("reverse: [%s]\n", reverseWords("hello  "));
	printf("reverse: [%s]\n", reverseWords(" hello "));
	printf("reverse: [%s]\n", reverseWords("  hello  "));
	printf("reverse: [%s]\n", reverseWords("hello world!"));
	printf("reverse: [%s]\n", reverseWords(" hello world!"));
	printf("reverse: [%s]\n", reverseWords("  hello world!"));
	printf("reverse: [%s]\n", reverseWords("hello world! "));
	printf("reverse: [%s]\n", reverseWords("hello world!  "));
	printf("reverse: [%s]\n", reverseWords(" hello world! "));
	printf("reverse: [%s]\n", reverseWords("  hello world!  "));
	printf("reverse: [%s]\n", reverseWords("hello  world!"));
	return 0;
}
