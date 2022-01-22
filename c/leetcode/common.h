#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define bool int
#define true 1
#define false 0

#define LOCAL_DEBUG
/*
 * int (*arr)[COL_SIZE] = (int (*)[COL_SIZE])_arr
 */

static int g_enableLog = 1;

#define DebugLog(fmt, ...) \
do { \
    if (g_enableLog) { \
        printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__); \
    } \
} while (0)

#define Log(...) DebugLog(__VA_ARGS__)

#define __printf(fmt, ...) \
({ \
    if (g_enableLog) { \
        printf(fmt, ##__VA_ARGS__); \
    } \
})

static inline void EnableDebugLog(void)
{
    g_enableLog = 1;
}

static inline void DisableDebugLog(void)
{
    g_enableLog = 0;
}

static inline void DoPrintArray(const char *func, int line, int *arr, int size)
{
    int i;
    printf("[%s:%d] array: ", func, line);
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
#define PrintArray(arr, size) DoPrintArray(__func__, __LINE__, arr, size)

static inline void DoPrintArray2(const char *func, int line, int **array,
                               int row, int col)
{
    int i, j;
    int (*arr)[col] = (int (*)[col])array;
    printf("[%s:%d] two dimensional array:\n", func, line);
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
#define PrintArray2(arr, row, col) \
        DoPrintArray2(__func__, __LINE__, arr, row, col)


static inline void DoPrintCharArray2(const char *func, int line, char **array,
                                     int row, int col)
{
    int i, j;
    char (*arr)[col] = (char (*)[col])array;
    printf("[%s:%d] two dimensional array:\n", func, line);
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
}
#define PrintCharArray2(arr, row, col) \
        DoPrintCharArray2(__func__, __LINE__, arr, row, col)

#define ArraySize(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARRAY_SIZE(arr) ArraySize(arr)

#endif /* __COMMON_H__ */
