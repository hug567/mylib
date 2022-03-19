/*
 * leetcode 42: 接雨水 [困难]
 * 2022-03-11
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int Min(int a, int b)
{
    return a < b ? a : b;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

int ArrayMax(int *arr, int size)
{
    int i;
    int max = 0;

    for (i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int Compare(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}

int *NextMax(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        if (arr[i] >= 0) {
            return arr + i;
        }
    }
    return NULL;
}

void DeleteOneValue(int *arr, int size, int val)
{
    for (int i = 0; i < size; i++) {
        if (arr[i] == val) {
            arr[i] = -1;
            return;
        }
    }
}

int *GetMaxNum(int *arr, int size, int val)
{
    int i;

    if (val >= arr[0]) {
        for (i = 1; i < size; i++) {
            if (arr[i] > 0) {
                return arr + i;
            }
        }
    } else {
        for (i = 1; i < size; i++) {
            if (arr[i] == val) {
                arr[i] = -1;
                return arr;
            }
        }
    }
    return NULL;
}

int trap(int *height, int heightSize)
{
    int trap = 0;
    int i, tmp;
    int left_max;
    int *right_max;
    int right_arr[1000];

    if (heightSize <= 2) {
        return 0;
    }
    left_max = height[0];
    memcpy(right_arr, height + 2, (heightSize - 2) * sizeof(int));
    qsort(right_arr, heightSize - 2, sizeof(int), Compare);
    //right_max = right_arr;
    for (i = 1; i < heightSize - 1; i++) {
        //left_max = Max(left_max, height[i]);
        if (i == 8) {
            Log("i = %d\n", i);
        }
        //Log("height[i] = %d\n", height[i]);
        //Log("height[%d] = %d\n", i, height[i]);
        left_max = left_max > height[i] ? left_max : height[i];
        right_max = GetMaxNum(right_arr + i - 1, heightSize - 1 - i, height[i + 1]);
        tmp = Min(left_max, *right_max) - height[i];
        trap += (tmp > 0 ? tmp : 0);
        //right_max = ArrayMax(height + i + 1, heightSize - i - 1);
        //if (*right_max == height[i + 1]) {
        //    right_max = NextMax(right_max + 1, (int)(right_arr - right_max + heightSize - 2ULL));
        //} else {
        //    DeleteOneValue(right_max, (int)(right_arr - right_max + heightSize - 1ULL), height[i + 1]);
        //
        //right_max = GetMaxNum()
    }

    return trap;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int arr[] = { 0,1,0,2,1,0,1,3,2,1,2,1 };
    int size = ARRAY_SIZE(arr);
    Log("trap: %d(6)\n", trap(arr, size));
}

void TestCase2(void)
{
    int arr[] = { 4,2,0,3,2,5 };
    int size = ARRAY_SIZE(arr);
    Log("trap: %d(9)\n", trap(arr, size));
}

int main(void)
{
    TestCase1();
    //TestCase2();
    return 0;
}
