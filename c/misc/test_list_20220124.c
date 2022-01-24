/*
 * 练习：带头节点的有序循环双链表的基本操作
 * 2022-01-24
 */
#include "common.h"

struct ListNode {
    int val;
    struct ListNode *next;
    struct ListNode *pre;
};

void ListNodeInit(struct ListNode *n, int val)
{
    n->val = val;
    n->next = n;
    n->pre = n;
}

struct ListNode *ListNodeAlloc(int val)
{
    struct ListNode *node = malloc(sizeof(struct ListNode));
    ListNodeInit(node, val);
    return node;
}

void ListNodeFree(struct ListNode *node)
{
    if (node != NULL) {
        free(node);
    }
}

struct ListNode *ListCreate(void)
{
    struct ListNode *head = ListNodeAlloc(0);
    return head;
}

void ListDestroy(struct ListNode *head)
{
    struct ListNode *cur = NULL, *post = NULL;

    for (cur = head->next, post = cur->next;
         cur != head;
         cur = post, post = post->next) {
             cur->pre->next = cur->next;
             cur->next->pre = cur->pre;
             free(cur);
    }
    free(head);
}

void ListInsertHead(struct ListNode *head, struct ListNode *new)
{
    struct ListNode *next = head->next;
    /* head <-> new <-> next */
    head->next = new;
    new->pre = head;
    new->next = next;
    next->pre = new;
}

void ListInsertTail(struct ListNode *head, struct ListNode *new)
{
    struct ListNode *tail = head->pre;
    /* tail <-> new <-> head */
    tail->next = new;
    new->pre = tail;
    new->next = head;
    head->pre = new;
}

void ListInsertAscend(struct ListNode *head, struct ListNode *new)
{
    struct ListNode *pre = head->next;
    struct ListNode *post = NULL;

    while (pre != head &&  pre->val < new->val) {
        pre = pre->next;
    }
    post = pre;
    pre = pre->pre;
    /* pre <-> new <-> post */
    pre->next = new;
    new->pre = pre;
    new->next = post;
    post->pre = new;
}

void ListInsertDescend(struct ListNode *head, struct ListNode *new)
{
    struct ListNode *pre = head->next;
    struct ListNode *post = NULL;

    while (pre != head &&  pre->val > new->val) {
        pre = pre->next;
    }
    post = pre;
    pre = pre->pre;
    /* pre <-> new <-> post */
    pre->next = new;
    new->pre = pre;
    new->next = post;
    post->pre = new;
}

void ListPrint(struct ListNode *head)
{
    struct ListNode *cur = head->next;

    Log("list: ");
    while (cur != head) {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

/***** 测试用例 ****************************************************************/
void TestCase1(void)
{
    int i;
    int arr[] = { 3, 5, 1, 2, 7, 0, 9, 8, 4, 6 };
    int size = ARRAY_SIZE(arr);
    struct ListNode *head = ListCreate();
    struct ListNode *new = NULL;

    for (i = 0; i < size; i++) {
        new = ListNodeAlloc(arr[i]);
        ListInsertHead(head, new);
    }
    ListPrint(head);

    ListDestroy(head);
}

void TestCase2(void)
{
    int i;
    int arr[] = { 3, 5, 1, 2, 7, 0, 9, 8, 4, 6 };
    int size = ARRAY_SIZE(arr);
    struct ListNode *head = ListCreate();
    struct ListNode *new = NULL;

    for (i = 0; i < size; i++) {
        new = ListNodeAlloc(arr[i]);
        ListInsertTail(head, new);
    }
    ListPrint(head);

    ListDestroy(head);
}

void TestCase3(void)
{
    int i;
    int arr[] = { 3, 5, 1, 2, 7, 0, 9, 8, 4, 6 };
    int size = ARRAY_SIZE(arr);
    struct ListNode *head = ListCreate();
    struct ListNode *new = NULL;

    for (i = 0; i < size; i++) {
        new = ListNodeAlloc(arr[i]);
        ListInsertAscend(head, new);
    }
    ListPrint(head);

    ListDestroy(head);
}

void TestCase4(void)
{
    int i;
    int arr[] = { 3, 5, 1, 2, 7, 0, 9, 8, 4, 6 };
    int size = ARRAY_SIZE(arr);
    struct ListNode *head = ListCreate();
    struct ListNode *new = NULL;

    for (i = 0; i < size; i++) {
        new = ListNodeAlloc(arr[i]);
        ListInsertDescend(head, new);
    }
    ListPrint(head);

    ListDestroy(head);
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    return 0;
}