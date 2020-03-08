/*
 * 题目：leetcode 912: 排序数组
 * 难度：中等
 * 技巧：递归实现快速排序
 * 时间：2020-03-04
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/* 插入排序：超出时间限制 */
int* sortArray1(int* nums, int numsSize, int* returnSize){
	int i, j, tmp;
	int *sorted = (int *)malloc(numsSize * sizeof(int));

	memcpy(sorted, nums, numsSize * sizeof(int));
	for (i = 0; i < numsSize - 1; i++) {
		for (j = i + 1; j < numsSize; j++) {
			if (sorted[i] > sorted[j]) {
				tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
		}
	}
	*returnSize = numsSize;
	return sorted;
}

/* 冒泡排序：超出时间限制 */
int* sortArray2(int* nums, int numsSize, int* returnSize){
	int i, j, tmp;
	int *sorted = (int *)malloc(numsSize * sizeof(int));

	memcpy(sorted, nums, numsSize * sizeof(int));
	for (i = 0; i < numsSize - 1; i++) {
		for (j = 0; j < numsSize - i - 1; j++) {
			if (sorted[j] > sorted[j + 1]) {
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
		}
	}
	*returnSize = numsSize;
	return sorted;
}

/* 归并排序： */
int* sortArray3(int* nums, int numsSize, int* returnSize){
	int i, j, tmp;
	int *sorted = (int *)malloc(numsSize * sizeof(int));

	memcpy(sorted, nums, numsSize * sizeof(int));
	*returnSize = numsSize;
	return sorted;
}

/* 快速排序：用时：76ms, 内存消耗：16.1MB */
void quick_sort(int *nums, int start, int end)
{
	if (start >= end) {
		return;
	}
	int i = start;
	int j = end;
	int tmp = nums[i]; /* 分界线 */

	while (i < j) {
		while (i < j && tmp <= nums[j]) {
			j--;
		}
		if (i < j) {
			nums[i] = nums[j];
			i++;
		}
		while (i < j && tmp > nums[i]) {
			i++;
		}
		if (i < j) {
			nums[j] = nums[i];
			j--;
		}
	}
	nums[i] = tmp;
	quick_sort(nums, start, i - 1);
	quick_sort(nums, i + 1, end);
}

/* 快速排序：用时：76ms, 内存消耗：16.1MB */
int* sortArray(int* nums, int numsSize, int* returnSize){
	int i, j, tmp;
	int *sorted = (int *)malloc(numsSize * sizeof(int));

	memcpy(sorted, nums, numsSize * sizeof(int));
	quick_sort(sorted, 0, numsSize - 1);
	*returnSize = numsSize;
	return sorted;
}

int main()
{
	int i;
	int nums[] = {5, 1, 1, 2, 0, 0};
	int numsSize = 6;
	int returnSize = 0;

	int *sorted = sortArray(nums, numsSize, &returnSize);
	for (i = 0; i < returnSize; i++) {
		printf("%d ", sorted[i]);
	}
	printf("\0");
	return 0;
}
