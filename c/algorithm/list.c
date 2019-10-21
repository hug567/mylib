/* 队列 */
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
	int data;
	struct LNode *next;
} LNode, LinkList;

LinkList* ListCreate(void)
{
	LinkList *list = (LinkList *)malloc(sizeof(LinkList));
	list->data = 0;
	list->next = NULL;
	return list;
}

int ListLength(LinkList *list)
{
	int len = 0;
	while (list != NULL && list->next != NULL) {
		len++;
		list = list->next;
	}
	return len;
}

void ListInsertHead(LinkList *list, int data)
{
	LNode *node = (LNode *)malloc(sizeof(LNode));
	node->data = data;
	node->next = list->next;
	list->next = node;
}

void ListInsertEnd(LinkList *list, int data)
{
	LinkList *l = list;
	LNode *node = (LNode *)malloc(sizeof(LNode));
	node->data = data;
	node->next = NULL;

	while (l != NULL && l->next != NULL) {
		l = l->next;
	}
	l->next = node;
}

void ListInsertAtIndex(LinkList *list, int pos, int data)
{
	while (list->next != NULL && pos > 0) {
		list = list->next;
		pos--;
	}
	if (pos > 1) {
		printf("List insert failed!\n");
		return;
	}
	LNode *node = (LNode *)malloc(sizeof(LNode));
	node->data = data;
	if (list->next == NULL) {
		node->next = NULL;
		list->next = node;
	} else {
		node->next = list->next;
		list->next = node;
	}
}

void ListDeleteAtIndex(LinkList *list, int pos)
{
	while (list->next != NULL && pos > 1) {
		list = list->next;
		pos--;
	}
	if (pos > 1) {
		printf("List delete failed!\n");
		return;
	}
	if (list->next->next == NULL) {
		list->next = NULL;
	} else {
		list->next = list->next->next;
	}
}

void ListDistory(LinkList *list)
{
	LNode *node = (LNode *)malloc(sizeof(LNode));
	while (list->next != NULL && list->next->next != NULL) {
		node = list->next->next;
		free(list->next);
		list->next = node;
	}
	free(list->next);
	free(list);
	free(node);
	list = NULL;
	node = NULL;
}

void ListPrint(LinkList *list)
{
	printf("list: ");
	while (list->next != NULL) {
		list = list->next;
		printf("%d ", list->data);
	}
	printf("\n");
}

int main()
{
	int i = 0;
	int err = 0;
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	int len = sizeof(data) / sizeof(int);

	LinkList *list = ListCreate();
	for (i = 0; i < len; i++) {
		ListInsertEnd(list, data[i]);
	}
	printf("length: %d\n", ListLength(list));
	ListPrint(list);
	ListInsertAtIndex(list, 3, 0);
	printf("length: %d\n", ListLength(list));
	ListPrint(list);
	ListDeleteAtIndex(list, 4);
	printf("length: %d\n", ListLength(list));
	ListPrint(list);
	ListDistory(list);
	return 0;
}
