/*
 * 练习：带头结点的循环双链表
 * 2021-03-02
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BUG_ON(exp) assert(exp)
#define debug_log(fmt, ...) {if (0) {printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__);}}

struct ListNode {
    int val;
    struct ListNode *pre;
    struct ListNode *next;
};

void PrintList(struct ListNode *head)
{
    struct ListNode *node = NULL;

    BUG_ON(head != NULL);
    node = head->next;
    printf("list: ");
    while (node != head) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

int IsEmpty(struct ListNode *head)
{
    BUG_ON(head != NULL);
    if (head->next == head) {
        return 1;
    } else {
        return 0;
    }
}

void ListInit(struct ListNode *head)
{
    BUG_ON(head != NULL);
    head->next = head;
    head->pre = head;
}

struct ListNode *ListNodeAlloc(int val)
{
    struct ListNode *node = NULL;
    node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = node;
    node->pre = node;
    return node;
}

void ListNodeDestroy(struct ListNode *node)
{
    if (node != NULL) {
        free(node);
    }
}

void InsertHead(struct ListNode *head, int val)
{
    struct ListNode *node = NULL;

    BUG_ON(head != NULL);
    node = ListNodeAlloc(val);
    node->next = head->next;
    head->next->pre = node;
    head->next = node;
    node->pre = head;
}

void InsertTail(struct ListNode *head, int val)
{
    struct ListNode *node = NULL;
    struct ListNode *tail = NULL;

    BUG_ON(head != NULL);
    node = ListNodeAlloc(val);
    tail = head->pre;
    tail->next = node;
    node->pre = tail;
    node->next = head;
    head->pre = node;
}

int DeleteHead(struct ListNode *head)
{
    int val;
    struct ListNode *node = NULL;

    BUG_ON(head != NULL);
    if (IsEmpty(head)) {
        return -1;
    }
    node = head->next;
    head->next = node->next;
    node->next->pre = head;
    val = node->val;
    ListNodeDestroy(node);
    return val;
}

int DeleteTail(struct ListNode *head)
{
    int val;
    struct ListNode *node = NULL;

    BUG_ON(head != NULL);
    if (IsEmpty(head)) {
        return -1;
    }
    node = head->pre;
    node->pre->next = head;
    head->pre = node->pre;
    val = node->val;
    ListNodeDestroy(node);
    return val;
}

int DeleteNodeByValue(struct ListNode *head, int val)
{}

void DestroyList(struct ListNode *head)
{
    while(!IsEmpty(head)) {
        DeleteHead(head);
    }
}

int main(void)
{
    int i;
    struct ListNode *head = NULL;

    head = ListNodeAlloc(0);
    for (i = 0; i < 5; i++) {
        InsertTail(head, i);
    }
    PrintList(head);
    for (i = 5; i < 10; i++) {
        InsertHead(head, i);
    }
    PrintList(head);

    DeleteHead(head);
    PrintList(head);

    DeleteTail(head);
    PrintList(head);

    ListNodeDestroy(head);
    head = NULL;
    return 0;
}
