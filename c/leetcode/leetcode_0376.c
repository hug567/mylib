/*
 * 题目：leetcode 376: 摆动序列
 * 难度：中等
 * 技巧：贪心思想
 * 时间：2020-03-30
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NeedCount(int pre, int cur)
{
	if (pre > 0 && cur < 0) {
		return 1;
	} else if (pre < 0 && cur > 0) {
		return 1;
	} else if (pre == 0 && cur != 0) {
		return 1;
	} else {
		return 0;
	}
}

int wiggleMaxLength(int* nums, int numsSize){
	int i;
	int flag;
	int tmp;
	int len = 1;

	if (numsSize <= 2) {
		if (numsSize == 2 && nums[0] != nums[1]) {
			return 2;
		} else if (numsSize == 0) {
			return 0;
		} else {
			return 1;
		}
	}

	flag = nums[1] - nums[0];
	if (flag != 0) {
		len++;
	}
	for (i = 1; i < numsSize - 1; i++) {
		tmp = nums[i + 1] - nums[i];
		if (NeedCount(flag, tmp)) {
			flag = tmp;
			len++;
		}
	}

	return len;
}

int main(int argc, char *argv[])
{
	//int nums[] = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
	//int nums[] = {1, 7, 4, 9, 2, 5};
	int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	int numsSize = sizeof(nums) / sizeof(int);
	printf("max length = %d\n", wiggleMaxLength(nums, numsSize));
	return 0;
}
