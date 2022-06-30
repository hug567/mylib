/*
 * leetcode 19: 删除链表的倒数第N个节点 [中等]
 * 2022-06-30
 */
#include "common.h"

struct ListNode {
     int val;
     struct ListNode *next;
};

/***** 提交代码 ******************************************************************/
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    int i, len = 0;
    struct ListNode *cur = head, *next;

    while (cur != NULL) {
        len++;
        cur = cur->next;
    }
    if (n == len) {
        return head->next;
    }
    cur = head;
    for (i = 0; i < len - n -1; i++) {
        cur = cur->next;
    }
    next = cur->next;
    cur->next = next->next;
    return head;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int i;
    int arr[] = {1, 2, 3, 4, 5};
    int size = ARRAY_SIZE(arr);
    struct ListNode *head = NULL, *cur = NULL, *tmp = NULL;

    for (i = 0; i < size; i++) {
        tmp = malloc(sizeof(struct ListNode));
        tmp->val = arr[i];
        tmp->next = NULL;
        if (i == 0) {
            head = tmp;
            cur = head;
        } else {
            cur->next = tmp;
            cur = tmp;
        }
    }
    head = removeNthFromEnd(head, 2);
    Log("list: ");
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    TestCase1();
    return 0;
}