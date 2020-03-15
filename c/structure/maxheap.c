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

#define MAX_SIZE 100

typedef struct {
	int data[MAX_SIZE];
	int count;
} Heap;

void heap_insert(Heap *h, int data)
{
	h->data[h->count] = data;
	h->count++;
}

int main()
{
	printf("hello heap\n");
	return 0;
}
