/*
 * leetcode 154: 寻找旋转排序数组中的最小值II [困难]
 * 思路：1）、二分查找，初始时区间最值为num[0]，区间右值为num[size-1]；
 *      2）、中值与区间右值比较，比右值大的在最小值的左侧，比右值小的在最小值的右侧，若中值
 *           等于右值，右值索引减一
 * 2022-04-14
 */
#include "common.h"

/****** 提交代码 *****************************************************************/
int findMin(int* nums, int numsSize){
    int left = 0;
    int right = numsSize - 1;
    int mid;

    while (left < right) {
        if (left + 1 == right) {
            return nums[left] < nums[right] ? nums[left] : nums[right];
        }
        mid = (left + right) / 2;
        if (nums[mid] > nums[right]) {
            left = mid;
        } else if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            right--;
        }
    }

    return nums[0];
}

/****** 本地调试 *****************************************************************/
void TestCase1(void)
{
    int nums[] = { 3, 4, 5, 1, 2 };
    int size = ARRAY_SIZE(nums);
    Log("min: %d(1)\n", findMin(nums, size));
}

void TestCase2(void)
{
    int nums[] = { 4, 5, 6, 7, 0, 1, 2 };
    int size = ARRAY_SIZE(nums);
    Log("min: %d(0)\n", findMin(nums, size));
}

void TestCase3(void)
{
    int nums[] = { 11, 13, 15, 17 };
    int size = ARRAY_SIZE(nums);
    Log("min: %d(11)\n", findMin(nums, size));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    return 0;
}