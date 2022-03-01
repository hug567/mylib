/*
 * leetcode 234: 回文链表 [简单]
 * 方案一：将链表数值复制到数组中，判断是不是回文数组
 * 方案二：将链表后半部分反转，两个指针分别指向链表前后两部分，判断是否相同
 * 2022-03-01
 */
#include "common.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

/***** 提交代码 ******************************************************************/
#define MAX_SIZE 100000
bool isPalindrome(struct ListNode* head)
{
    int size = 0;
    int *arr = NULL;
    int *h = NULL, *t = NULL;

    arr = malloc(MAX_SIZE * sizeof(int));
    while (head != NULL) {
        arr[size] = head->val;
        head = head->next;
        size++;
    }
    h = arr;
    t = h + size - 1;
    while (h < t) {
        if (*h != *t) {
            return false;
        }
        h++;
        t--;
    }
    free(arr);
    return true;
}

/***** 本地调试 ******************************************************************/
struct ListNode *CreateListByArray(int *arr, int size)
{
    int i;
    struct ListNode *head = NULL;
    struct ListNode *tail = NULL;
    struct ListNode *tmp = NULL;

    for (i = 0; i < size; i++) {
        tmp = malloc(sizeof(struct ListNode));
        tmp->val = arr[i];
        tmp->next = NULL;
        if (head == NULL) {
            head = tmp;
            tail = tmp;
        } else {
            tail->next = tmp;
            tail = tmp;
        }
    }
    return head;
}

void DestroyList(struct ListNode *head)
{
    struct ListNode *tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void TestCase1(void)
{
    int arr[] = { 1, 2, 2, 1 };
    int size = ARRAY_SIZE(arr);
    struct ListNode *head = CreateListByArray(arr, size);
    Log("is palindrome: %d(1)\n", isPalindrome(head));
    DestroyList(head);
}

void TestCase2(void)
{
    int arr[] = { 1, 2 };
    int size = ARRAY_SIZE(arr);
    struct ListNode *head = CreateListByArray(arr, size);
    Log("is palindrome: %d(0)\n", isPalindrome(head));
    DestroyList(head);
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}
