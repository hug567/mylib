/* leetcode 1: 两数之和(简单) */
#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
	int *sum = (int *)malloc(2 * sizeof(int));

	*returnSize = 2;
	return sum;
}

int main()
{
	int i;
	int sum = 0;

	for (i = 1; i <= 100; i++) {
		sum += i;
	}
	printf("sum = %d\n", sum);
	return 0;
}
