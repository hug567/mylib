/* leetcode 632: 最小区间 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getMinMax(int *nums, int size, int *min, int *minPos, int *max)
{
	int i;
	*min = nums[0];
	*minPos = 0;
	*max = nums[0];

	for (i = 1; i < size; i++) {
		if (*min > nums[i]) {
			*min = nums[i];
			*minPos = i;
		}
		if (*max < nums[i]) {
			*max = nums[i];
		}
	}
}

int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize)
{
	int i, j;
	int min, max, minPos, retMin, retMax;
	int *range = (int *)malloc(2 * sizeof(int));
	int *index = (int *)malloc(numsSize * sizeof(int));
	int *cur = (int *)malloc(numsSize * sizeof(int));
	int maxCol = *numsColSize;

	for (i = 1; i < numsSize; i++) {
		if (maxCol < *(numsColSize + i)) {
			maxCol = *(numsColSize + i);
		}
	}

	/* 本地编译获取二维数组 */
	int (*data)[maxCol] = (int(*)[maxCol])nums;

	/* leetcode获取二维数组 */
	//int **data = nums;

	for (i = 0; i < numsSize; i++) {
		index[i] = 0;
		cur[i] = data[i][0];
	}
	getMinMax(cur, numsSize, &retMin, &minPos, &retMax);

	int flag = 1;
	while (flag) {
		getMinMax(cur, numsSize, &min, &minPos, &max);
		if (((max - min) < (retMax - retMin)) ||
			(((max - min) == (retMax - retMin)) && (min < retMin))) {
			retMin = min;
			retMax = max;
		}
		index[minPos]++;
		for (i = 0; i < numsSize; i++) {
			if (index[i] >= numsColSize[i]) {
				flag = 0;
			}
		}
		if (flag) {
			cur[minPos] = data[minPos][index[minPos]];
		}
	}

	range[0] = retMin;
	range[1] = retMax;
	*returnSize = 2;
	return range;
}

int main()
{
	int nums[3][5] = {{4, 10, 15, 24, 26},
			  {0, 9, 12, 20},
			  {5, 18, 22, 30}};
	int numsSize = 3;
	int numsColSize[3] = {5, 4, 4};
	int returnSize[2] = {0, 0};

	int *range = smallestRange((int **)nums, numsSize, numsColSize, returnSize);
	printf("smallest range: [%d, %d]\n", range[0], range[1]);
	return 0;
}
