/*
 * 题目：leetcode 215: 数组中第k大的元素
 * 难度：中等
 * 技巧：维护一个k个不重复元素的最小堆
 * 时间：2020-03-15
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 100

struct Heap {
	int *data;
	int size;
	int maxSize;
};

struct Heap *CreateHeap()
{
	struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
	heap->data = (int *)malloc((MAXSIZE + 1) * sizeof(int));
	heap->size = 0;
	heap->maxSize = MAXSIZE;
}

void InsertNode(struct Heap *heap, int data)
{
	int i;
	int tmp;

	if (heap == NULL || heap->size >= heap->maxSize) {
		return;
	}

	heap->size++;
	heap->data[heap->size] = data;
	i = heap->size;
	while (i > 1) {
		if (i / 2 >= 1 && heap->data[i] < heap->data[i / 2]) {
			tmp = heap->data[i];
			heap->data[i] = heap->data[i / 2];
			heap->data[i / 2] = tmp;
		} else {
			break;
		}
		i /= 2;
	}
}

void RefreshTop(struct Heap *heap, int data)
{
	int i = 1;
	int tmp;

	heap->data[1] = data;
	while (i <= heap->size) {
		if (2 * i <= heap->size && heap->data[i] > heap->data[2 * i]) {
			tmp = heap->data[i];
			heap->data[i] = heap->data[2 * i];
			heap->data[2 * i] = tmp;
		} else if ((2 * i + 1) <= heap->size && heap->data[i] > heap->data[2 * i + 1]) {
			tmp = heap->data[i];
			heap->data[i] = heap->data[2 * i + 1];
			heap->data[2 * i + 1] = tmp;
		} else {
			return;
		}
	}
}

int NotExist(struct Heap *heap, int data)
{
	int i;
	for (i = 1; i <= heap->size; i++) {
		if (heap->data[i] == data) {
			return 0;
		}
	}
	return 1;
}

int findKthLargest(int* nums, int numsSize, int k){
	int i;
	struct Heap *heap = CreateHeap();

	for (i = 0; i < numsSize; i++) {
		if (heap->size < k && NotExist(heap, nums[i])) {
			InsertNode(heap, nums[i]);
		} else if (heap->size == k && heap->data[1] < nums[i]) {
			RefreshTop(heap, nums[i]);
		}
	}

	return heap->data[1];
}

int main(int argc, char *argv[])
{
	int nums[] = {3, 2, 1, 5, 6, 4};
	int numsSize = 6;
	int k = 2;

	printf("kth num = %d\n", findKthLargest(nums, numsSize, k));
	return 0;
}
