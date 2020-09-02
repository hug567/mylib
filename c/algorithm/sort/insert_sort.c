/*
 * 插入排序：将未排序序列的首元素，插入已排序序列的合适位置
 * 时间复杂度：
 * 空间复杂度：
 * 2020-09-02
 */
#include <stdio.h>

void InsertSort(int *arr, int size)
{
    int i, j;
    int tmp;

    for (i = 1; i < size; i++) {
        for (j = 0; j < i; j++) {
            if (arr[j] > arr[i]) {
                tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }
}

int main(void)
{
    int i;
    int arr[] = {5, 9, 3, 6, 2, 8, 1, 0, 4, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    InsertSort(arr, size);
    printf("sort: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
