/*
 * 题目：leetcode 55: 跳跃游戏
 * 难度：中等
 * 技巧：
 * 时间：2020-04-06
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool CurCanJump(int *nums, int pos)
{
	int i;
	for (i = 0; i < pos; i++) {
		/* 可跳过位置在pos的值为0的元素的条件 */
		if (nums[i] > pos - i) {
			return true;
		}
	}
	return false;
}

bool canJump(int* nums, int numsSize){
	int i;

	if (numsSize <= 1) {
		return true;
	}
	for (i = 0; i < numsSize; i++) {
		/* 可直接跳至末尾 */
		if (nums[i] >= numsSize - i - 1) {
			return true;
		}
		/* 元素为0且不可跳过 */
		if (nums[i] == 0 && !CurCanJump(nums, i)) {
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[])
{
	//int nums[] = {2, 3, 1, 1, 4};
	//int nums[] = {3, 2, 1, 0, 4};
	//int nums[] = {0};
	int nums[] = {2, 0, 0};

	int numsSize = sizeof(nums) / sizeof(int);
	printf("can jump: %d\n", canJump(nums, numsSize));
	return 0;
}
