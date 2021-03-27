/*
 * leetcode 2 [中等]：两数相加
 * 2021-03-27
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

/***** 本地调试 ****************************************************************/
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *InsertTail(struct ListNode *head, int val);

struct ListNode *CreateListByArray(int *arr, int size)
{
    int i;
    struct ListNode *head = NULL;
    for (i = 0; i < size; i++) {
        head = InsertTail(head, arr[i]);
    }
    return head;
}

void PrintList(struct ListNode *head)
{
    printf("list: ");
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

/***** 提交代码 ****************************************************************/
struct ListNode *InsertTail(struct ListNode *head, int val)
{
    struct ListNode *tail = NULL;
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    if (head == NULL) {
        return node;
    }
    tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
    return head;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    int v1, v2;
    int flag = 0;
    int num = 0;
    struct ListNode *node = NULL;

    while (l1 != NULL || l2 != NULL) {
        if (l1 == NULL) {
            v1 = 0;
        } else {
            v1 = l1->val;
        }
        if (l2 == NULL) {
            v2 = 0;
        } else {
            v2 = l2->val;
        }
        num = v1 + v2 + flag;
        node = InsertTail(node, num % 10);
        flag = num / 10;
        if (l1 != NULL) {
            l1 = l1->next;
        }
        if (l2 != NULL) {
            l2 = l2->next;
        }
    }
    if (flag > 0) {
        node = InsertTail(node, flag);
    }
    return node;
}

/***** 本地调试 ****************************************************************/

int main(void)
{
    int arr1[] = { 2, 4, 3 };
    int arr2[] = { 5, 6, 4 };
    struct ListNode *l1 = CreateListByArray(arr1, sizeof(arr1) / sizeof(arr1[0]));
    struct ListNode *l2 = CreateListByArray(arr2, sizeof(arr2) / sizeof(arr2[0]));
    struct ListNode *ls = addTwoNumbers(l1, l2);
    PrintList(ls);

    return 0;
}
