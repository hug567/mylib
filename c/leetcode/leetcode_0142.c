/* leetcode 142: 环形链表II(中等) */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode *detectCycle(struct ListNode *head)
{
	struct ListNode *slow = head, *fast = head;

	while (fast != NULL && fast->next != NULL) {
		/* 快慢指针 */
		slow = slow->next;
		fast = fast->next->next;
		if (fast == NULL || fast->next == NULL) {
			return NULL;
		} if (slow == fast) {
			while (fast != head) {
				fast = fast->next;
				head = head->next;
			}
			return fast;
		}
	}
	return NULL;
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

	tmp = detectCycle(head);
	if (tmp != NULL) {
		i = 0;
		while (tmp != head) {
			i++;
			head = head->next;
		}
		printf("pos = %d\n", i);
	} else {
		printf("pos = -1, no cycle\n");
	}

	return 0;
}
