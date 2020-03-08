/*
 * 题目：leetcode 1: 两数之和
 * 难度：简单
 * 技巧：无
 * 时间：2020-03-08
 */
#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
	if (nums == NULL) {
		*returnSize = 0;
		return NULL;
	}
	int i;
	int j;
	int *index = (int *)malloc(2 * sizeof(int));

	for (i = 0; i < numsSize - 1; i++) {
		for (j = i + 1; j < numsSize; j++) {
			if (nums[i] + nums[j] == target) {
				index[0] = i;
				index[1] = j;
				*returnSize = 2;
				return index;
			}
		}
	}
	*returnSize = 0;
	return NULL;
}

int main()
{
	int i;
	int nums[] = {2, 7, 11, 15};
	int numsSize = sizeof(nums) / sizeof(int);
	int target = 9;
	int returnSize = 0;
	int *index = NULL;

	index = twoSum(nums, numsSize, target, &returnSize);
	printf("sum index: ");
	for (i = 0; i < returnSize; i++) {
		printf("%d ", index[i]);
	}
	printf("\n");

	return 0;
}
