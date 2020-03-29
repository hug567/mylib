/*
 * 练习：堆排序
 * 作者：huangxing567@163.com
 * 时间：2020-03-29
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

/*
 * 下标从1开始
 * 父节点：i/2
 * 子节点：2i、2i+1
 */
struct Heap {
	int *data;
	int size;
	int maxSize;
};

struct Heap *CreateHeap(void)
{
	struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
	heap->size = 0;
	heap->maxSize = MAXSIZE;
	heap->data = (int *)malloc((MAXSIZE + 1) * sizeof(int));
	(void)memset(heap->data, 0, (MAXSIZE + 1) * sizeof(int));
	return heap;
}

void InsertNode(struct Heap *heap, int data)
{
	int i;

	if (heap->size >= heap->maxSize) {
		return;
	}
	heap->size++; /* 下标从1开始 */
	for (i = heap->size; i > 1 && heap->data[i/2] < data; i /= 2) {
		heap->data[i] = heap->data[i/2];
	}
	heap->data[i] = data;
}

void PrintHeap(struct Heap *heap)
{
	int i;

	printf("heap: ");
	for (i = 0; i < heap->size; i++) {
		printf("%d ", heap->data[i + 1]);
	}
	printf("\n");
}

int main()
{
	int i;
	struct Heap *heap = CreateHeap();

	for (i = 0; i < 10; i++) {
		InsertNode(heap, i);
	}
	PrintHeap(heap);
	return 0;
}
