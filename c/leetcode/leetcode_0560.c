/* leetcode 560: 和为K的子数组 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int subarraySum(int *nums, int numsSize, int k)
{
	int i = 0, j = 0;
	int sum = 0, result = 0;

	for (i = 0; i < numsSize; i++) {
		sum = 0;
		for (j = i; j < numsSize; j++) {
			sum += *(nums + j);
			if (sum == k) {
				result++;
			} else if (sum > k) {
				continue;
			}
		}
	}
	return result;
}

int main()
{
	int nums[] = {1, 1, 1};
	int numsSize = 3;
	int k = 2;
	printf("result = %d\n", subarraySum(nums, numsSize, k));
	return 0;
}
