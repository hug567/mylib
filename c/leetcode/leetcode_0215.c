/*
 * 题目：leetcode 215: 数组中第k大的元素
 * 难度：中等
 * 技巧：
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
	struct Heap *heap = (struct heap *)malloc(sizeof(struct Heap));
	heap->data = (int *)malloc((MAXSIZE + 1) * sizeof(int));
	heap->size = 0;
	heap->maxSize = MAXSIZE;
}

void InsertNode(struct Heap *heap, int data)
{
	if (heap == NULL || heap->size >= heap->maxSize) {
		return;
	}
}

int findKthLargest(int* nums, int numsSize, int k){
	struct Heap *heap = CreateHeap();


	return 0;
}

int main(int argc, char *argv[])
{
	int nums[] = {3, 2, 1, 5, 6, 4};
	int numsSize = 6;
	int k = 2;

	printf("kth num = %d\n", findKthLargest(nums, numsSize, k));
	return 0;
}
