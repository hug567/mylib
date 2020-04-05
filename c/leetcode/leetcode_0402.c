/*
 * 题目：leetcode 402: 移掉k位数字
 * 难度：中等
 * 技巧：双链表便于删除，执行k次，每次删除序列递减开始的元素
 * 时间：2020-04-05
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int gLen = 0;

struct Node {
	char data;
	struct Node *pre;
	struct Node *next;
};

struct Node *CreateNumList(char *num)
{
	struct Node *head = NULL;
	struct Node *tail = NULL;
	while (*num != '\0') {
		if (head == NULL) {
			head = (struct Node *)malloc(sizeof(struct Node));
			head->data = *num;
			head->pre = NULL;
			head->next = NULL;
			tail = head;
		} else {
			tail->next = (struct Node *)malloc(sizeof(struct Node));
			tail->next->pre = tail;
			tail = tail->next;
			tail->data = *num;
			tail->next = NULL;
		}
		num++;
		gLen++;
	}

	return head;
}

void DestoryNumList(struct Node *head)
{
	struct Node *cur = head;
	if (head == NULL) {
		return;
	}
	while (head->next != NULL) {
		head = head->next;
		free(cur);
		cur = head;
	}
	free(head);
	gLen = 0;
}

struct Node *DeleteNode(struct Node *head)
{
	struct Node *cur = head;
	struct Node *pre = NULL;

	if (head == NULL) {
		gLen = 0;
		return NULL;
	} else if (head->next == NULL) {
		free(head);
		gLen = 0;
		return NULL;
	}
	if (head->next->data - head->data < 0) {
		cur = head->next;
		cur->pre = NULL;
		free(head);
		gLen--;
		return cur;
	}
	while (cur->next != NULL) {
		if (cur->data > cur->next->data) {
			pre = cur->pre;
			pre->next = cur->next;
			cur->next->pre = pre;
			free(cur);
			gLen--;
			return head;
		}
		cur = cur->next;
	}
	pre = cur->pre;
	pre->next = NULL;
	free(cur);
	gLen--;

	return head;
}

void PrintList(struct Node *head)
{
	printf("num: ");
	while (head != NULL) {
		printf("%c", head->data);
		head = head->next;
	}
	printf("\n");
}

char *SaveMinNum(struct Node *head)
{
	int flag = 0;
	char *ret = (char *)malloc((gLen + 1) * sizeof(char));
	char *tmp = ret;
	memset(ret, '\0', gLen + 1);

	if (head == NULL) {
		return "0";
	}
	while (head != NULL && head->data == '0') {
		head = head->next;
	}
	if (head == NULL) {
		return "0";
	}
	while (head != NULL) {
		*tmp = head->data;
		tmp++;
		head = head->next;
	}
	return ret;
}

char *removeKdigits(char *num, int k) {
	int i;
	int len = strlen(num);
	struct Node *head = NULL;
	char *ret = NULL;

	if (k == len) {
		return "0";
	}

	head = CreateNumList(num);
	for (i = 0; i < k; i++) {
		head = DeleteNode(head);
	}
	ret = SaveMinNum(head);
	DestoryNumList(head);
	return ret;
}

int main(int argc, char *argv[])
{
	char *num = "1432219";
	int k = 3;
	//char *num = "10200";
	//int k = 1;
	//char *num = "10";
	//int k = 2;
	//char *num = "112";
	//int k = 1;

	printf("min num = %s\n", removeKdigits(num, k));
	return 0;
}
