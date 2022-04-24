/*
 * leetcode 264: 丑数II [中等]
 * 题目：给定整数n，计算第n个丑数
 * 定义：丑数是质因子只包含2、3、5的正整数，1也是丑数
 * 思路：三指针
 *      1）、第一个丑数是1，从丑数序列中从小到大依次取出一个数，其值的2、3、5倍均是丑数；
 *      三个索引值i、j、k，其储值均为0，表示丑数序列第一个值，比较3个值2*num[i]、3*num[j]、
 *      5*num[k]，取三个值的最小值，其对应的索引值+1，判断计算出的丑数是否已存在，若存在，则
 *      跳过，若不存在，则存储到丑数序列尾部，继续计算下一个丑数
 *      2）、判断数值是否已存在，可用二分查找；
 * 2022-04-21
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
int ThreeMin(int a, int b, int c)
{
    int min;

    min = a < b ? a : b;
    min = min < c ? min : c;
    return min;
}

/* 二分查找判断递增数组中是否存在指定值 */
bool NumExist(int *num, int size, int target)
{
    int left = 0;
    int right = size - 1;
    int mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (num[mid] == target) {
            return true;
        } else if (num[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return false;
}

int nthUglyNumber(int n)
{
    int count = 0;
    int i = 0, j = 0, k = 0;
    int tmp;
    int *num = malloc(n * sizeof(int));

    num[0] = 1;
    count++;
    while (count < n) {
        tmp = ThreeMin(2 * num[i], 3 * num[j], 5 * num[k]);
        if (tmp == 2 * num[i]) {
            i++;
        } else if (tmp == 3 * num[j]) {
            j++;
        } else if (tmp == 5 * num[k]) {
            k++;
        }
        if (NumExist(num, count, tmp)) {
            continue;
        }
        num[count] = tmp;
        count++;
    }
    tmp = num[count - 1];
    free(num);
    return tmp;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    Log("uglay num: %d(12)\n", nthUglyNumber(10));
    Log("uglay num: %d(1)\n", nthUglyNumber(1));
    Log("uglay num: %d(15)\n", nthUglyNumber(11));
}

int main(void)
{
    TestCase1();
    return 0;
}