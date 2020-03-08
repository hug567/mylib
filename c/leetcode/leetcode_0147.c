/*
 * 题目：leetcode 147: 对链表进行插入排序
 * 难度：中等
 * 技巧：
 * 时间：2020-03-08
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* insertionSortList(struct ListNode* head){
	if (head == NULL) {
		return;
	}
	struct ListNode *cur = head;
	struct ListNode *pre = NULL;
	struct ListNode *lat = NULL;

	while (cur->next != NULL) {
		while (cur->val <= cur->next->val) {
			cur = cur->next;
		}
	}

	return head;
}

static struct ListNode *CreateList(const int *nums, const int size)
{
	if (size <= 0) {
		return NULL;
	}
	int i;
	struct ListNode *head = NULL;
	struct ListNode *tail = NULL;

	for (i = 0; i < size; i++) {
		if (head == NULL) {
			head = (struct ListNode *)malloc(sizeof(struct ListNode));
			head->val = nums[i];
			head->next = NULL;
			tail = head;
		} else {
			tail->next = (struct ListNode *)malloc(sizeof(struct ListNode));
			tail->next->val = nums[i];
			tail->next->next = NULL;
			tail = tail->next;
		}
	}
	return head;
}

static void PrintList(const struct ListNode *head)
{
	if (head == NULL) {
		return;
	}
	while (head != NULL) {
		printf("%d ", head->val);
		head = head->next;
	}
	(void)printf("\n");
}

int main(int argc, char *argv[])
{
	int i;
	int nums[] = {-1, 5, 3, 4, 0};
	int numsSize = sizeof(nums) / sizeof(int);
	struct ListNode *list = CreateList(nums, numsSize);

	(void)printf("list: ");
	PrintList(list);
	list = insertionSortList(list);
	(void)printf("sorted: ");
	PrintList(list);

	return 0;
}
