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

#define PrintArray(arr, size) \
do { \
    int __i; \
    int *__arr = arr; \
    int __size = size; \
    DebugLog("array: "); \
    for (__i = 0; __i < __size; __i++) { \
        printf("%d ", __arr[__i]); \
    } \
    printf("\n"); \
} while (0)

#define PrintArray2(__array, __row_, __col_) \
do { \
    int __i, __j; \
    int __row = (__row_); \
    int __col = (__col_); \
    int (*__arr)[__col] = (int (*)[__col])__array; \
    Log("array:\n"); \
    for (__i = 0; __i < __row; __i++) { \
        for (__j = 0; __j < __col; __j++) { \
            printf("%d ", __arr[__i][__j]); \
        } \
        printf("\n"); \
    } \
} while (0)

#define PrintCharArray2(__array, __row_, __col_) \
do { \
    int __i, __j; \
    int __row = (__row_); \
    int __col = (__col_); \
    char (*__arr)[__col] = (char (*)[__col])__array; \
    Log("array:\n"); \
    for (__i = 0; __i < __row; __i++) { \
        for (__j = 0; __j < __col; __j++) { \
            printf("%c ", __arr[__i][__j]); \
        } \
        printf("\n"); \
    } \
} while (0)

#define ArraySize(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARRAY_SIZE(arr) ArraySize(arr)

#endif /* __COMMON_H__ */
