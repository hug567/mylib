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

void SwapInt(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

struct Heap *CreateHeap(void)
{
	struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
	heap->data = (int *)malloc((MAXSIZE + 1) * sizeof(int));
	heap->size = 0;
	heap->maxSize = MAXSIZE;
	return heap;
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

int SinkBig(struct Heap *heap, int parent)
{
	int left = 2 * parent;
	int right = 2 * parent + 1;
	int tmp;

	if (left > heap->size ||
	    (right > heap->size && heap->data[parent] <= heap->data[left]) ||
	    (right <= heap->size && heap->data[parent] <= heap->data[left] &&
	     heap->data[parent] <= heap->data[right])) {
		return 0;
	}
	if ((right > heap->size)  ||
	    (heap->data[parent] > heap->data[left] && heap->data[parent] <= heap->data[right]) ||
	    (heap->data[parent] > heap->data[right]  && heap->data[right]) > heap->data[left]) {
		SwapInt(&heap->data[parent], &heap->data[left]);
		return left;
	}
	if ((heap->data[left] >= heap->data[parent] && heap->data[parent] > heap->data[right]) ||
	    (heap->data[parent] > heap->data[left]  && heap->data[left]) > heap->data[right]) {
		SwapInt(&heap->data[parent], &heap->data[right]);
		return right;
	}
}

void RefreshTop(struct Heap *heap, int data)
{
	int pos = 1;

	heap->data[1] = data;
	do {
		pos = SinkBig(heap, pos);
	} while (pos);
}

void PrintHeap(struct Heap *heap)
{
	int i;

	printf("heap: ");
	for (i = 1; i <= heap->size; i++) {
		printf("%d ", heap->data[i]);
	}
	printf("\n");
}

int findKthLargest(int* nums, int numsSize, int k){
	int i;
	struct Heap *heap = CreateHeap();

	for (i = 0; i < k; i++) {
		InsertNode(heap, nums[i]);
	}
PrintHeap(heap);
	for (i = k; i < numsSize; i++) {
		if (heap->data[1] < nums[i]) {
			RefreshTop(heap, nums[i]);
PrintHeap(heap);
		}
	}

	return heap->data[1];
}

int main(int argc, char *argv[])
{
	//int nums[] = {3, 2, 1, 5, 6, 4};
	//int numsSize = 6;
	//int k = 2;
	int nums[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
	int numsSize = sizeof(nums) / sizeof(int);
	int k = 4;

	printf("kth num = %d\n", findKthLargest(nums, numsSize, k));
	return 0;
}
