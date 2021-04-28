#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define LOCAL_DEBUG

static int g_enableLog = 1;

#define DebugLog(fmt, ...) \
({ \
    if (g_enableLog) { \
        printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__); \
    } \
})

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

void PrintArray(int *arr, int size)
{
    int i;
    printf("array: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

#endif