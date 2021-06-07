/*
 * 堆排序
 * 2021-06-07
 */
#include "../common.h"

#define MAX_SIZE 100

void MaxHeapInsert(int *heap, int val)
{
    int i, tmp;
    if (heap == NULL || heap[0] >= MAX_SIZE) {
        return;
    }
    heap[0]++;
    heap[heap[0]] = val;
    i = heap[0];
    while (i > 1) {
        if (heap[i] <= heap[i / 2]) {
            break;
        }
        tmp = heap[i];
        heap[i] = heap[i / 2];
        heap[i / 2] = tmp;
        i /= 2;
    }
}

int MaxHeapDeleteTop(int *heap)
{
    int i, top, tmp, idx;
    if (heap == NULL || heap[0] >= MAX_SIZE || heap[0] < 1) {
        return INT_MIN;
    }
    top = heap[1];
    heap[1] = heap[heap[0]];
    heap[0]--;
    i = 1;
    while (1) {
        idx = i;
        if (2 * i <= heap[0] && heap[idx] < heap[2 * i]) {
            idx = 2 * i;
        }
        if (2 * i + 1 <= heap[0] && heap[idx] < heap[2 * i + 1]) {
            idx = 2 * i + 1;
        }
        if (idx == i) {
            break;
        }
        tmp = heap[i];
        heap[i] = heap[idx];
        heap[idx] = tmp;
        i = idx;
    }
    return top;
}

void MinHeapInsert(int *heap, int val)
{
    int i, tmp;
    heap[0]++;
    heap[heap[0]] = val;
    i = heap[0];
    while (i > 1) {
        if (heap[i] >= heap[i / 2]) {
            break;
        }
        tmp = heap[i];
        heap[i] = heap[i / 2];
        heap[i / 2] = tmp;
        i /= 2;
    }

}

int MinHeapDeleteTop(int *heap)
{
    int i, top, tmp, idx;
    if (heap == NULL || heap[0] >= MAX_SIZE || heap[0] < 1) {
        return INT_MIN;
    }
    top = heap[1];
    heap[1] = heap[heap[0]];
    heap[0]--;
    i = 1;
    while (1) {
        idx = i;
        if (2 * i <= heap[0] && heap[idx] > heap[2 * i]) {
            idx = 2 * i;
        }
        if (2 * i + 1 <= heap[0] && heap[idx] > heap[2 * i + 1]) {
            idx = 2 * i + 1;
        }
        if (idx == i) {
            break;
        }
        tmp = heap[i];
        heap[i] = heap[idx];
        heap[idx] = tmp;
        i = idx;
    }
    return top;
}

void HeapSortAscend(int *arr, int size)
{
    int i;
    int heap[MAX_SIZE] = {0};
    for (i = 0; i < size; i++) {
        MinHeapInsert(heap, arr[i]);
    }
    for (i = 0; i < size; i++) {
        arr[i] = MinHeapDeleteTop(heap);
    }
}

void HeapSortDescend(int *arr, int size)
{
    int i;
    int heap[MAX_SIZE] = {0};
    for (i = 0; i < size; i++) {
        MaxHeapInsert(heap, arr[i]);
    }
    for (i = 0; i < size; i++) {
        arr[i] = MaxHeapDeleteTop(heap);
    }
}

int main(void)
{
    int arr[] = {5, 9, 3, 6, 2, 8, 1, 0, 4, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    PrintArray(arr, size);
    HeapSortAscend(arr, size);
    PrintArray(arr, size);
    HeapSortDescend(arr, size);
    PrintArray(arr, size);

    return 0;
}
