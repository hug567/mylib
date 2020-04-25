/*
 * 堆: 用数组实现的二叉树
 * 当前节点：i(i>0)
 * 父节点：i/2
 * 左子节点：2*i
 * 右子节点：2*i+1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

struct Heap{
	int *data;
	int count;
	int size;
};

struct Heap *HeapCreate(int size)
{
	struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
	/* index start from 1 */
	heap->data = (int *)malloc((size + 1) * sizeof(int));
	(void)memset(heap->data, 0, (size + 1) * sizeof(int));
	heap->count = 0;
	heap->size = size;
	return heap;
}

void HeapDestory(struct Heap *heap)
{
	if (heap != NULL) {
		if (heap->data != NULL) {
			free(heap->data);
		}
		free(heap);
	}
}

void HeapInsert(struct Heap *heap, int data)
{
	if (heap->count < heap->size) {
		heap->count++;  /* start from index 1 */
		heap->data[heap->count] = data;
	} else {
		printf("insert error, heap is full\n");
	}
}

void HeapPrint(struct Heap *heap)
{
	int i;

	printf("heap: ");
	for (i = 1; i <= heap->count; i++) {
		printf("%d ", heap->data[i]);
	}
	printf("\n");
}

int main()
{
	int i;
	struct Heap *heap = HeapCreate(MAX_SIZE);

	for (i = 0; i < 10; i ++) {
		HeapInsert(heap, i);
	}
	HeapPrint(heap);
	return 0;
}
