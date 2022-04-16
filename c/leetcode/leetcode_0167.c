/*
 * leetcode 167: 两数之和II-输入有序数组
 * 思路：对于第i个至nums[i]，在剩余数组中使用二分查找是否有target-nums[i]
 * 2022-04-15
 */
#include "common.h"
/****** 提交代码 *****************************************************************/
int BinarySearch(int *nums, int left, int right, int target)
{
    int mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize)
{
    int i;
    int *ret = malloc(2 * sizeof(int));

    for (i = 0; i < numbersSize - 1; i++) {
        ret[0] = i;
        ret[1] = BinarySearch(numbers, i + 1, numbersSize - 1, target - numbers[ret[0]]);
        if (ret[1] > 0) {
            break;
        }
    }

    *returnSize = 2;
    ret[0]++;
    ret[1]++;
    return ret;
}

/****** 本地调试 *****************************************************************/
void TestCase1(void)
{
    int nums[] = {2, 7, 11, 5};
    int size = ARRAY_SIZE(nums);
    int target = 9;
    int retSize;
    int *ret = twoSum(nums, size, target, &retSize);
    Log("ret: [%d, %d](1, 2)\n", ret[0], ret[1]);
    free(ret);
}

int main(void)
{
    TestCase1();
    return 0;
}