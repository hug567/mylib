/*
 * 公共头文件
 * 2021-04-14
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define LOCAL_DEBUG

#define DebugLog(fmg, ...) printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

void PrintArray(const int *arr, int size)
{
    int i;

    printf("arr: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void PrintArray2(int **_arr, int row, int col)
{
    int i, j;
    int (*arr)[col] = (int(*)[col])_arr;

    printf("arr2: \n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
