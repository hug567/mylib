/*
 * 选择排序：从未排序的序列中选择最小(大)的元素，与未排序序列的起始元素交换
 * 时间复杂度：O(n^2)
 * 空间复杂度：O(1)
 */
#include <stdio.h>

void SelectSort(int *arr, int size)
{
    int i, j;
    int temp;
    int index;

    for (i = 0; i < size - 1; i++) {
        index = i;
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[index]) { /* <: 为升序， >: 为降序 */
                index = j;
            }
        }
        if (index != i) {
            temp = arr[i];
            arr[i] = arr[index];
            arr[index] = temp;
        }
    }
}

int main(void)
{
    int i;
    int arr[] = {5, 9, 3, 6, 2, 8, 1, 0, 4, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    SelectSort(arr, size);
    printf("sort: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
