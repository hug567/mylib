/* leetcode 21: 合并两个有序链表(简单) */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
	if (l1 == NULL && l2 == NULL) {
		return NULL;
	} else if (l1 == NULL) {
		return l2;
	} else if (l2 == NULL) {
		return l1;
	}

	struct ListNode *head = NULL, *tail = NULL;
	struct ListNode *min = NULL;

	while (l1 != NULL || l2 != NULL) {
		if (l1 != NULL && l2 != NULL) {
			if (l1->val < l2->val) {
				min = l1;
				l1 = l1->next;
			} else {
				min = l2;
				l2 = l2->next;
			}
			if (head == NULL) {
				head = min;
				tail = min;
			} else {
				tail->next = min;
				tail = tail->next;
			}
		} else if (l1 == NULL) {
			tail->next = l2;
			tail = tail->next;
			l2 = l2->next;
		} else if (l2 == NULL) {
			tail->next = l1;
			tail = tail->next;
			l1 = l1->next;
		}
	}
	if (tail != NULL) {
		tail->next = NULL;
	}

	return head;
}

int main()
{
	int i;
	int val1[] = {1, 2, 4};
	int val2[] = {1, 3, 4};
	struct ListNode *l1 = NULL, *l2 = NULL;
	struct ListNode *next = NULL, *tmp = NULL;

	/* 构造链表 */
	for (i = 0; i < sizeof(val1) / sizeof(int); i++) {
		next = (struct ListNode *)malloc(sizeof(struct ListNode));
		next->val = val1[i];
		next->next = NULL;
		if (i == 0) {
			l1 = next;
			tmp = next;
		} else {
			tmp->next = next;
			tmp = next;
		}
	}
	for (i = 0; i < sizeof(val2) / sizeof(int); i++) {
		next = (struct ListNode *)malloc(sizeof(struct ListNode));
		next->val = val2[i];
		next->next = NULL;
		if (i == 0) {
			l2 = next;
			tmp = next;
		} else {
			tmp->next = next;
			tmp = next;
		}
	}

	tmp = l1;
	printf("list1 : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");
	tmp = l2;
	printf("list2 : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	tmp = mergeTwoLists(l1, l2);
	printf("merge list : ");
	while (tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	return 0;
}
