/*
 * 公共头文件
 * 2021-04-14
 */
#ifndef __MISC_COMMON_H__
#define __MISC_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define LOCAL_DEBUG

#define DebugLog(fmt, ...) \
        printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define Log(...) DebugLog(__VA_ARGS__)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define mem_zero_s(s) memset(&(s), 0, sizeof(s))
#define mem_zero_a(a) memset(a, 0, sizeof(a))

static inline void DoPrintArray(const char *func, int line,
                                const int *arr, int size)
{
    int i;

    printf("[%s:%d] arr: ", func, line);
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
#define PrintArray(__func__, __LINE__, arr, size)

static inline void DoPrintArray2(const char *func, int line,
                                 int **_arr, int row, int col)
{
    int i, j;
    int (*arr)[col] = (int(*)[col])_arr;

    printf("[%s:%d] arr2: \n", func, line);
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
#define PrintArray2(arr, row, col) \
        DoPrintArray2(__func__, __LINE__, (int **)(arr), row, col)

#endif