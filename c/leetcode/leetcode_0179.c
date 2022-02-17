/*
 * leetcode 179: 最大数 [中等]
 * 方法：用qsort排序，在compare函数中，对于比较的两个数，放在组合数前面，组成的数
*        更大的数，认为其更大，按降序排列，拍完序后，依次将数字转换成字符串，再连接起来
 * 2022-02-17
 */
#include "common.h"

/***** 提交代码 ****************************************************************/
#define MAX_INT_LEN 10
#define MAX_CHARS_LEN 400

void Int2Str(int num, char *str, int maxsize)
{
    char tmp;
    int i = 0, len;

    memset(str, 0, maxsize);
    if (num == 0) {
        str[0] = '0';
        return;
    }
    while (num > 0) {
        str[i] = num % 10 + '0';
        num /= 10;
        i++;
    }
    len = i;
    for (i = 0; i < len / 2; i++) {
        tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

int CompatrStr(char *str1, char *str2)
{
    char num_str1[20] = {0};
    char num_str2[20] = {0};

    strcat(num_str1, str1);
    strcat(num_str1, str2);
    strcat(num_str2, str2);
    strcat(num_str2, str1);
    return strcmp(num_str2, num_str1);
}

int Compare(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    char str1[MAX_INT_LEN], str2[MAX_INT_LEN];

    Int2Str(x, str1, MAX_INT_LEN);
    Int2Str(y, str2, MAX_INT_LEN);
    return CompatrStr(str1, str2);
}

int IsAllZero(int *num, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        if (num[i] != 0) {
            return 0;
        }
    }
    return 1;
}

char * largestNumber(int* nums, int numsSize)
{
    int i;
    char tmp[MAX_INT_LEN] = {0};
    char *str = malloc(MAX_CHARS_LEN);

    memset(str, 0, MAX_CHARS_LEN);
    if (IsAllZero(nums, numsSize)) {
        str[0] = '0';
        return str;
    }

    qsort(nums, numsSize, sizeof(int), Compare);
    for (i = 0; i < numsSize; i++) {
        Int2Str(nums[i], tmp, MAX_INT_LEN);
        strcat(str, tmp);
    }
    return str;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int num[] = { 10, 2 };
    int size = ARRAY_SIZE(num);
    Log("largest num: %s(210)\n", largestNumber(num, size));
}

void TestCase2(void)
{
    int num[] = { 3, 30, 34, 5, 9 };
    int size = ARRAY_SIZE(num);
    Log("largest num: %s(9634330)\n", largestNumber(num, size));
}

void TestCase3(void)
{
    int num[] = { 1 };
    int size = ARRAY_SIZE(num);
    Log("largest num: %s(1)\n", largestNumber(num, size));
}

void TestCase4(void)
{
    int num[] = { 10 };
    int size = ARRAY_SIZE(num);
    Log("largest num: %s(10)\n", largestNumber(num, size));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    return 0;
}