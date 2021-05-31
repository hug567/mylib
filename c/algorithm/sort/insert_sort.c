/*
 * 插入排序：将未排序序列的首元素，插入已排序序列的合适位置
 * 时间复杂度：
 * 空间复杂度：
 * 2020-09-02
 */
#include "../common.h"

void InsertSort(int *arr, int size)
{
    int i, j;
    int tmp;

    for (i = 1; i < size; i++) {
        for (j = 0; j < i; j++) {
            if (arr[j] > arr[i]) { /* >: 升序, <: 降序 */
                tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }
}

int AscendCompare(int a, int b)
{
    return a - b;
}

int DescendCompare(int a, int b)
{
    return b - a;
}

void InsertSort2(int *arr, int size, int (*comp)(int a, int b))
{
    int i, j, tmp;
    for (i = 1; i < size; i++) {
        for (j = 0; j < i; j++) {
            if (comp(arr[j], arr[i]) > 0) {
                tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }
}

int main(void)
{
    int arr[] = {5, 9, 3, 6, 2, 8, 1, 0, 4, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    PrintArray(arr, size);
    InsertSort(arr, size);
    PrintArray(arr, size);

    int arr2[] = {5, 9, 3, 6, 2, 8, 1, 0, 4, 7};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    PrintArray(arr2, size2);
    InsertSort2(arr2, size2, AscendCompare);
    PrintArray(arr2, size2);

    int arr3[] = {5, 9, 3, 6, 2, 8, 1, 0, 4, 7};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    PrintArray(arr3, size3);
    InsertSort2(arr3, size3, DescendCompare);
    PrintArray(arr3, size3);

    return 0;
}
