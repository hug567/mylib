/* leetcode 86: 分隔链表(中等) */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode *partion(struct ListNode *head, int x)
{
	if (head == NULL) {
		return NULL;
	}
	struct ListNode *less_head = NULL, *more_head = NULL;
	struct ListNode *less = NULL, *more = NULL;
	while (head != NULL) {
		if (head->val < x) {
			if (less_head == NULL) {
				less_head = head;
				less = less_head;
			} else {
				less->next = head;
				less = less->next;
			}
		} else {
			if (more_head == NULL) {
				more_head = head;
				more = more_head;
			} else {
				more->next = head;
				more = more->next;
			}
		}
		head = head->next;
	}
	if (more_head == NULL) {
		less->next = NULL;
		return less_head;
	} else if (less_head == NULL) {
		more->next = NULL;
		return more_head;
	} else {
		less->next = more_head;
		more->next = NULL;
		return less_head;
	}
}

int main()
{
	int i;
	int val[] = {1, 4, 3, 2, 5, 2};
	struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *next = NULL, *tmp = NULL;
	head->val = val[0];
	head->next = NULL;

	/* 构造链表 */
	tmp = head;
	for (i = 1; i < sizeof(val) / sizeof(int); i++) {
		next = (struct ListNode *)malloc(sizeof(struct ListNode));
		next->val = val[i];
		next->next = NULL;
		tmp->next = next;
		tmp = next;
	}

	/* 输出链表 */
	tmp = head;
	printf("list : ");
	for (i = 0; i < sizeof(val) / sizeof(int); i++) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	tmp = partion(head, 3);
	printf("list : ");
	for (i = 0; i < sizeof(val) / sizeof(int); i++) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	return 0;
}
