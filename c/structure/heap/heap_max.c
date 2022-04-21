/*
 * 练习：最大堆
 * 当前节点：i(i>0)
 * 父节点：i/2
 * 左子节点：2*i
 * 右子节点：2*i+1
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

int DeleteTop(struct Heap *heap)
{
	int top;
	int i;
	int tmp;

	if (heap->size == 0) {
		printf("heap is empty\n");
		exit(1);
	}

	top = heap->data[1];
	heap->data[1] = heap->data[heap->size];
	heap->size--;
	i = 1;
	/* 错误：当两个子节点都比父节点大时，父节点应与较大的子节点交换 */
	while (i <= heap->size) {
		if (2 * i <= heap->size && heap->data[i] < heap->data[2 * i]) {
			tmp = heap->data[i];
			heap->data[i] = heap->data[2 * i];
			heap->data[2 * i] = tmp;
			i = 2 * i;
		} else if (2 * i + 1 <= heap->size && heap->data[i] < heap->data[2 * i + 1]) {
			tmp = heap->data[i];
			heap->data[i] = heap->data[2 * i + 1];
			heap->data[2 * i + 1] = tmp;
			i = 2 * i + 1;
		} else {
			break;
		}
	}

	return top;
}

int HeapTop(struct Heap *heap)
{
	return heap->data[1]; /* 从1开始存储 */
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
	printf("heap size: %d\n", heap->size);
	printf("heap top: %d\n", HeapTop(heap));
	PrintHeap(heap);
	printf("heap:\n");
	printf("           9\n");
	printf("         /  \\\n");
	printf("        8    5\n");
	printf("       / \\  / \\\n");
	printf("      6   7 1 4\n");
	printf("     / \\ /\n");
	printf("    0  3 2\n");
	printf("delete top: %d\n", DeleteTop(heap));
	PrintHeap(heap);
	return 0;
}
