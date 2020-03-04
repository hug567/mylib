/*
 * 题目：leetcode 784: 字母大小写全排列
 * 难度：简单
 * 时间：2020-03-04
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pow_int(int a, int n)
{
	int i;
	int num = 1;

	for (i = 0; i < n; i++) {
		num = num * a;
	}
	return num;
}

char *flip(char *S, unsigned int num, int count, int *pos)
{
	int i;
	int len = strlen(S);
	char *str = (char *)malloc(len + 1);
	unsigned int tmp;
	int idx;

	memset(str, '\0', len + 1);
	memcpy(str, S, len + 1);

	for (i = 0; i < count; i++) {
		tmp = num >> i;
		if (tmp & 0x1) {
			idx = *(pos + i);
			if (*(str + idx) >= 'a' && *(str + idx) <= 'z') {
				*(str + idx) = *(str + idx) - 'a' + 'A';
			}
			else {
				*(str + pos[i]) = *(str + pos[i]) - 'A' + 'a';
			}
		}
	}

	return str;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCasePermutation(char * S, int* returnSize){
	int i;
	int j;
	unsigned int count = 0;
	char *tmp = S;
	int len = strlen(S);

	while(*tmp != '\0') {
		if ((*tmp >= 'a' && *tmp <= 'z') || (*tmp >= 'A' && *tmp <= 'Z')) {
			count++;
		}
		tmp++;
	}

	if (count == 0) {
		*returnSize = 1;
		char **strs = (char **)malloc(sizeof(char *));
		strs[0] = S;
		return strs;
	}

	j = 0;
	tmp = S;
	int *pos = (int *)malloc(sizeof(int) * count);
	memset(pos, 0, sizeof(int) * count);
	for (i = 0; i < len; i++) {
		if ((*tmp >= 'a' && *tmp <= 'z') || (*tmp >= 'A' && *tmp <= 'Z')) {
			pos[j] = i;
			j++;
		}
		tmp++;
	}

	*returnSize = pow_int(2, count);
	char **strs = (char **)malloc(sizeof(char *) * *returnSize);
	for (i = 0; i < *returnSize; i++) {
		strs[i] = flip(S, i, count, pos);
	}

	return strs;
}

int main()
{
	int i;
	int returnSize = 0;
	char *s = "a1b2";
	char **strs = letterCasePermutation(s, &returnSize);

	for (i = 0; i < returnSize; i++) {
		printf("strs[i] = %s\n", strs[i]);
	}

	return 0;
}
