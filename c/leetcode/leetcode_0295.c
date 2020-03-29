/*
 * 题目：leetcode 295: 数据流的中位数
 * 难度：困难
 * 技巧：双向链表插入排序
 * 其他：用一个最大堆一个最小堆分别保存，未实现
 * 时间：2020-03-27
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
	int num;
	struct Node *pre;
	struct Node *next;
};

/* initialize your data structure here. */
typedef struct {
	struct Node *head;
	int len;
} MedianFinder;

MedianFinder* medianFinderCreate() {
	MedianFinder *obj = (MedianFinder *)malloc(sizeof(MedianFinder));
	obj->head = NULL;
	obj->len = 0;
	return obj;
}

static void InsertToHead(MedianFinder *obj, struct Node *node)
{
	if (obj->len == 0) {
		obj->head = node;
	} else {
		node->next = obj->head;
		obj->head->pre = node;
		obj->head = node;
	}
	obj->len++;
}

static void InsertToMiddle(MedianFinder *obj, struct Node *node)
{
	struct Node *tmp = obj->head;

	while (tmp->next != NULL) {
		if (tmp->next->num >= node->num) {
			break;
		}
		tmp = tmp->next;
	}
	if (tmp->next == NULL) { /* insert to tail */
		tmp->next = node;
		node->pre = tmp;
	} else { /* insert to middle */
		node->next = tmp->next;
		tmp->next->pre = node;
		tmp->next = node;
		node->pre = tmp;
	}
	obj->len++;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
	int i;
	int pos;
	struct Node *tmp = NULL;
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));

	node->num = num;
	node->pre = NULL;
	node->next = NULL;
	if (obj->len == 0 || obj->head->num >= num) {
		InsertToHead(obj, node);
	} else {
		InsertToMiddle(obj, node);
	}
}

double medianFinderFindMedian(MedianFinder* obj) {
	int i;
	struct Node *tmp = obj->head;

	for (i = 0; i < obj->len / 2; i++) {
		tmp = tmp->next;
	}
	if (obj->len % 2 == 1) {
		return tmp->num;
	} else {
		return (tmp->pre->num + tmp->num) / 2.0;
	}
}

void medianFinderFree(MedianFinder* obj) {
	int i;
	struct Node *node = NULL;
	for (i = 0; i < obj->len; i++) {
		node = obj->head;
		obj->head = obj->head->next;
		free(node);
	}
	free(obj);
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);

 * double param_2 = medianFinderFindMedian(obj);

 * medianFinderFree(obj);
*/

int main(int argc, char *argv[])
{
	MedianFinder *obj = medianFinderCreate();

	medianFinderAddNum(obj, -1);
	medianFinderAddNum(obj, -2);
	printf("mdiean = %f\n", medianFinderFindMedian(obj));
	medianFinderAddNum(obj, -3);
	medianFinderAddNum(obj, -4);
	medianFinderAddNum(obj, -5);
	printf("mdiean = %f\n", medianFinderFindMedian(obj));
	medianFinderFree(obj);

	return 0;
}
