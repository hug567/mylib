/*
 * 最大堆: 
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
	for (i = heap->size; heap->data[i/2] < data && i > 0; i /= 2) {
		heap->data[i] = heap->data[i/2];
	}
	heap->data[i] = data;
}

void DeleteNode(struct Heap *heap)
{
	int parent;
	int child;
	int last; /* 最后一个节点 */

	if (heap->size == 0) {
		return;
	}

	last = heap->data[heap->size];
	heap->size--;
	for (parent = 1; 2 * parent < heap->size; parent = child) {
		child = 2 * parent;
		if (child != heap->size && heap->data[child] < heap->data[child + 1]) {
			child++;
			if (last < heap->data[child]) {
				heap->data[parent] = heap->data[child];
			} else {
				break;
			}
		}
	}
	heap->data[parent] = last;
}

int HeapTop(struct Heap *heap)
{
	return heap->data[1]; /* 从1开始存储 */
}

int main()
{
	int i;
	struct Heap *heap = CreateHeap();

	for (i = 0; i < 10; i++) {
		InsertNode(heap, i);
	}
	printf("heap size: %d\n", heap->size);
	return 0;
}
