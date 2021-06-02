#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define LOCAL_DEBUG

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
