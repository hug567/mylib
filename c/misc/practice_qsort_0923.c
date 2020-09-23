/*
 * 练习：C语言排序函数qsort
 * 2020-09-23
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b)
{
    //return *(int *)a - *(int *)b; /* 升序 */
    return *(int *)b - *(int *)a; /* 降序 */
}

int main(void)
{
    int i;
    int arr[] = {4, 8, 3, 1, 0, 2, 5, 7, 6, 9};
    int size = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, size, sizeof(int), compare);

    printf("sort: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}