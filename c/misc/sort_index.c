/*
 * 对数组排序，原数组不变，获取排序后的索引数组
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void PrintArray(const int *arr, int size)
{
    int i;
    printf("array: ");
    for (i = 0; i < size; i++) {
        printf("%2d ", arr[i]);
    }
    printf("\n");
}

void PrintArrayBySortIndex(const int *arr, int size, const int *idx_arr)
{
    int i;
    printf("array: ");
    for (i = 0; i < size; i++) {
        printf("%2d ", arr[idx_arr[i]]);
    }
    printf("\n");
}

void RandowNum(int *arr, int size)
{
    int i;
    srand(time(0));
    for (i = 0; i < size; i++) {
        arr[i] = rand() % 10;
    }
}

/* qsort升序比较 */
int Compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

/* 值相同的个数 */
int EqualNum(const int *arr, int size, const int *idx_arr, int start)
{
    int i;
    int count = 1;
    for (i = start + 1; i < size; i++) {
        if (arr[idx_arr[i]] == arr[idx_arr[start]]) {
            count++;
        } else {
            break;
        }
    }
    return count;
}

/* 值相同，索引小的在前面，对值相同的索引数组做升序排序 */
void UpdateIndexArr(const int *arr, int size, int *idx_arr)
{
    int i = 0;
    int equal_num;

    while (i < size - 1) {
        if (arr[idx_arr[i] == arr[idx_arr[i + 1]]]) {
            equal_num = EqualNum(arr, size, idx_arr, i);
            qsort(idx_arr + i, equal_num, sizeof(int), Compare);
            i += equal_num;
        } else {
            i++;
        }
    }
}

/*
 * 索引数组：在不改变原数组的情况下，对齐排序
 *          创建一个索引数组，初始化为递增序列: 0,1,2,3...，
 *          当值相同时，索引小的值在前面
 */
void GetSortIndex(const int *arr, int size, int *idx_arr)
{
    int i, j, tmp;

    for (i = 0; i < size; i++) {
        idx_arr[i] = i;
    }
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (arr[idx_arr[i]] > arr[idx_arr[j]]) {
                tmp = idx_arr[i];
                idx_arr[i] = idx_arr[j];
                idx_arr[j] = tmp;
            }
        }
    }
    UpdateIndexArr(arr, size, idx_arr);
}

int *g_arr = NULL;
/* qsort比较 */
int Compare2(const void *a, const void *b)
{
    return g_arr[*(int *)a] - g_arr[*(int *)b];
}

/* 基于qsort实现获取索引数组 */
void GetSortIndex2(const int *arr, int size, int *idx_arr)
{
    int i;
    g_arr = arr;

    for (i = 0; i < size; i++) {
        idx_arr[i] = i;
    }
    qsort(idx_arr, size, sizeof(int), Compare2);
    UpdateIndexArr(arr, size, idx_arr);
}

int main(void)
{
    int arr[10] = {0};
    int size = sizeof(arr) / sizeof(arr[0]);
    int idx_arr[10] = {0};

    printf("test case 1:\n");
    RandowNum(arr, size);
    PrintArray(arr, size);
    GetSortIndex(arr, size, idx_arr);
    PrintArray(arr, size);
    PrintArray(idx_arr, size);
    PrintArrayBySortIndex(arr, size, idx_arr);

    printf("test case 2:\n");
    //RandowNum(arr, size);
    PrintArray(arr, size);
    GetSortIndex2(arr, size, idx_arr);
    PrintArray(arr, size);
    PrintArray(idx_arr, size);
    PrintArrayBySortIndex(arr, size, idx_arr);

    return 0;
}
