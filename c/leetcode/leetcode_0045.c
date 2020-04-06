/*
 * 题目：leetcode 45: 跳跃游戏II
 * 难度：困难
 * 技巧：贪心思想：从前到后找到一个可一次调到末尾的值，count加1，更新末尾
 * 时间：2020-04-06
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int jumpToEnd(int *nums, int end)
{
	int i;
	for (i = 0; i < end; i++) {
		if (nums[i] >= end -i) {
			return i;
		}
	}
	return -1;
}

int jump(int* nums, int numsSize){
	int count = 0;
	int end = numsSize - 1;

	if (numsSize <= 1) {
		return 0;
	}
	while ((end = jumpToEnd(nums, end)) >= 0) {
		count++;
	}
	return count;
}

int main(int argc, char *argv[])
{
	int nums[] = {2, 3, 1, 1, 4};
	//int nums[] = {3, 2, 1, 0, 4};
	//int nums[] = {0};
	//int nums[] = {2, 0, 0};

	int numsSize = sizeof(nums) / sizeof(int);
	printf("min jump times: %d\n", jump(nums, numsSize));
	return 0;
}
