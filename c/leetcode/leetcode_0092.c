/* leetcode 92: 反转链表II(简单) */
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* reverseBetween(struct ListNode* head, int m, int n)
{
	if (m == n) {
		return head;
	}

	int i = 0, flag = 0;
	struct ListNode *before = head;
	struct ListNode *start = head;
	struct ListNode *pre, *cur, *next;

	if (m > 1) {
		for (i = 0; i < m - 2; i++) {
			before = before->next;
		}
		start = before->next;
	}

	i = 0;
	pre = start;
	cur = pre->next;
	while (i < n - m) {
		if (cur->next != NULL) {
			next = cur->next;
			cur->next = pre;
			pre = cur;
			cur = next;
		} else {
			cur->next = pre;
			flag = 1;
			break;
		}
		i++;
	}
	if (m > 1 && flag == 0 ) {
		before->next = pre;
		start->next = cur;
	} else if (m > 1 && flag == 1) {
		before->next = cur;
		start->next = NULL;
	} else if (m == 1 & flag == 0) {
		before->next = cur;
		head = pre;
	} else {
		start->next = NULL;
		head = cur;
	}

	return head;
}

int main()
{
	int i, m, n;
	struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *next = NULL;
	struct ListNode *tmp = NULL;
	head->val = 1;
	head->next = NULL;
	tmp = head;
	for (i = 2; i < 6; i++) {
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

	m = 2;
	n = 5;
	tmp = reverseBetween(head, m, n);
	printf("list : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	return 0;
}
