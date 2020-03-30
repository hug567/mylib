/*
 * 题目：leetcode 455: 分发饼干
 * 难度：简单
 * 技巧：1、C语言快排库函数qsort升序排列孩子与饼干
 *       2、贪心思想，先用最少的饼干尝试满足一个孩子
 * 时间：2020-03-29
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b; /* ascend */
}

int findContentChildren(int* g, int gSize, int* s, int sSize){
	int i = 0;
	int j = 0;
	int count = 0;

	qsort(g, gSize, sizeof(int), compare);
	qsort(s, sSize, sizeof(int), compare);
	while (i < gSize && j < sSize) {
		if (g[i] <= s[j]) {
			count++;
			i++;
			j++;
		} else {
			j++;
		}
	}

	return count;
}

int main(int argc, char *argv[])
{
//	int g[] = {1, 2, 3}; /* child */
//	int gSize = sizeof(g) / sizeof(int);
//	int s[] = {1, 1}; /* cookie */
//	int sSize = sizeof(s) / sizeof(int);

	int g[] = {1, 2}; /* child */
	int gSize = sizeof(g) / sizeof(int);
	int s[] = {1, 2, 3}; /* cookie */
	int sSize = sizeof(s) / sizeof(int);

	printf("max meet = %d\n", findContentChildren(g, gSize, s, sSize));

	return 0;
}
