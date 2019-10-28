/* leetcode 141: 环形链表(简单) */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

bool hasCycle(struct ListNode *head)
{
	struct ListNode *slow = head, *fast = head;

	while (fast != NULL && fast->next != NULL) {
		/* 快慢指针 */
		slow = slow->next;
		fast = fast->next->next;
		if (fast == NULL || fast->next == NULL) {
			return false;
		} if (slow == fast) {
			return true;
		}
	}
	return false;
}

int main()
{
	int i;
	int val[] = {3, 2, 0, -4};
	struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *next = NULL, *tmp = NULL;
	head->val = val[0];
	head->next = NULL;

	/* 构造环形链表 */
	tmp = head;
	for (i = 1; i < 4; i++) {
		next = (struct ListNode *)malloc(sizeof(struct ListNode));
		next->val = val[i];
		next->next = NULL;
		tmp->next = next;
		tmp = next;
	}
	tmp->next = head->next;

	tmp = head;
	printf("list : ");
	for (i = 0; i < 4; i++) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");

	if (hasCycle(head)) {
		printf("true\n");
	} else {
		printf("false\n");
	}

	return 0;
}
