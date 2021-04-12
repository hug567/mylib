#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define LOCAL_DEBUG

#define DebugLog(fmt, ...) if (1) {printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__);}

void PrintArray(int *arr, int size)
{
    int i;
    printf("array: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
