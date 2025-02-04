#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define LOCAL_DEBUG

//#define INT_MAX ((int)(~0U >> 1))
//#define INT_MIN ((int)(1U << 31))

static int g_enableLog = 1;

static inline void EnableDebugLog(void)
{
    g_enableLog = 1;
}

static inline void DisableDebugLog(void)
{
    g_enableLog = 0;
}

#define __printf(fmt, ...) \
do { \
    if (g_enableLog == 1) { \
        printf(fmt, ##__VA_ARGS__); \
    } \
} while (0)

#define DebugLog(fmt, ...) \
do { \
        __printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__); \
} while (0)
#define Log(...) DebugLog(__VA_ARGS__)
#define LogEnter() Log("Enter %s\n", __func__)

#define PrintArray(arr, size) \
do { \
    int __i; \
    int *__arr = arr; \
    int __size = size; \
    DebugLog("array: "); \
    for (__i = 0; __i < __size; __i++) { \
        __printf("%d ", __arr[__i]); \
    } \
    __printf("\n"); \
} while (0) \

#endif /* __COMMON_H__ */
