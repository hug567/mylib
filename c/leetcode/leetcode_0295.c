/*
 * 题目：leetcode 295: 数据流的中位数
 * 难度：困难
 * 技巧：使用链表保存数据
 * 时间：2020-03-27
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
	int num;
	struct Node *next;
};

typedef struct {
	struct Node *head;
	struct Node *middle;
	int len;
} MedianFinder;

/** initialize your data structure here. */

MedianFinder* medianFinderCreate() {
	MedianFinder *obj = (MedianFinder *)malloc(sizeof(MedianFinder));
	obj->head = NULL;
	obj->middle = NULL;
	obj->len = 0;
	return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	node->num = num;
	node->next = NULL;
	if (obj->len == 0) {
		obj->head = node;
		obj->middle = node;
	} else {
	}
	obj->len++;
}

double medianFinderFindMedian(MedianFinder* obj) {

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
	return 0;
}
