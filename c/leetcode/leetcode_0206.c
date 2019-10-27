/* leetcode 206: 反转链表(简单) */
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* reverseList(struct ListNode* head)
{
	struct ListNode *pre = head;
	struct ListNode *next = NULL;

	head = head->next;
	next = head;
	pre->next = NULL;
	while (head->next != NULL) {
		next = head->next;
		head->next = pre;
		pre = head;
		head = next;
	}
	head->next = pre;

	return head;
}

int main()
{
	int i;
	struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *next = NULL;
	struct ListNode *tmp = NULL;
	head->val = 0;
	head->next = NULL;
	tmp = head;
	for (i = 1; i < 5; i++) {
		next = (struct ListNode *)malloc(sizeof(struct ListNode));
		next->val = i;
		next->next = NULL;
		tmp->next = next;
		tmp = next;
	}

	tmp = head;
	printf("list : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	tmp = reverseList(head);
	printf("list : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	return 0;
}
