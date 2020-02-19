/* 无向图，边带权，十字链表 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT (int)((~0U) >> 1)
#define MIN_INT (int)(1 << (8 * sizeof(int) - 1))
#define MAX_SIZE 100

typedef struct _arc {
	int head;
	int tail;
	struct _arc *hlink;
	struct _arc *tlink;
} Arc;

typedef struct _vex {
	int data;
	struct _arc *first_in;
	struct _arc *first_out;
} Vex;

typedef struct vex_node {
}

int main()
{
	printf("hello graph3\n");
	return 0;
}
