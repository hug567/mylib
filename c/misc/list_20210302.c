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

/***** 带头结点的循环双链表 *****************************************************/
struct ListNode {
    int val;
    struct ListNode *pre;
    struct ListNode *next;
};

int IsEmpty(struct ListNode *head)
{
    BUG_ON(head != NULL);
    if (head->next == head) {
        return 1;
    } else {
        return 0;
    }
}

struct ListNode *AllocNode(int val)
{
    struct ListNode *node = NULL;
    node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = node;
    node->pre = node;
    return node;
}

void DestroyNode(struct ListNode *node)
{
    if (node != NULL) {
        free(node);
    }
}

void InsertHead(struct ListNode *head, int val)
{
    struct ListNode *node = NULL;

    BUG_ON(head != NULL);
    node = AllocNode(val);
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
    node = AllocNode(val);
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
    DestroyNode(node);
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
    DestroyNode(node);
    return val;
}

int DeleteNodeByValue(struct ListNode *head, int val)
{
    struct ListNode *pre = NULL;
    struct ListNode *cur = NULL;
    struct ListNode *tmp = NULL;

    BUG_ON(head != NULL);
    pre = head;
    cur = head->next;
    while (cur != head) {
        if (cur->val == val) {
            tmp = cur;
            cur = cur->next;
            pre->next = cur;
            cur->pre = pre;
            DestroyNode(tmp);
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
    return val;
}

int ListLength(struct ListNode *head)
{
    int len = 0;
    struct ListNode *node = NULL;

    BUG_ON(head != NULL);
    node = head->next;
    while (node != head) {
        len++;
        node = node->next;
    }
    return len;
}

void DestroyList(struct ListNode *head)
{
    while(!IsEmpty(head)) {
        DeleteHead(head);
    }
}

void PrintList(struct ListNode *head)
{
    struct ListNode *node = NULL;

    BUG_ON(head != NULL);
    node = head->next;
    printf("list(%2d): ", ListLength(head));
    while (node != head) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

void TestList(void)
{
    int i;
    struct ListNode *head = NULL;

    printf("----- test list -----\n");
    head = AllocNode(0);
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

    DeleteNodeByValue(head, 0); //删除中间元素
    PrintList(head);
    DeleteNodeByValue(head, 8); //删除头部元素
    PrintList(head);
    DeleteNodeByValue(head, 3); //删除尾部元素
    PrintList(head);

    DestroyList(head);
    DestroyNode(head);
    head = NULL;
}
/***** 基于双链表的队列 ********************************************************/

void EnQueue(struct ListNode *head, int val)
{
    BUG_ON(head != NULL);
    InsertTail(head, val);
}

int DeQueue(struct ListNode *head)
{
    int val;

    BUG_ON(head != NULL);
    if (IsEmpty(head)) {
        return -1;
    }
    val = head->next->val;
    DeleteHead(head);
    return val;
}

void DestroyQueue(struct ListNode *head)
{
    BUG_ON(head != NULL);
    DestroyList(head);
}

void TestQueue(void)
{
    int i;
    struct ListNode *queue = AllocNode(0);

    printf("----- test queue -----\n");
    for (i = 0; i < 10; i++) {
        EnQueue(queue, i);
    }
    PrintList(queue);

    printf("queue head: %d\n", DeQueue(queue));
    PrintList(queue);

    DestroyList(queue);
    DestroyNode(queue);
    queue = NULL;
}
/***** 基于双链表的堆栈 ********************************************************/

void PushStack(struct ListNode *s, int val)
{
    BUG_ON(s != NULL);
    InsertHead(s, val);
}

int PopStack(struct ListNode *s)
{
    int val;

    BUG_ON(s != NULL);
    if (IsEmpty(s)) {
        return -1;
    }
    val = s->next->val;
    DeleteHead(s);
    return val;
}

void DestroyStack(struct ListNode *s)
{
    BUG_ON(s != NULL);
    DestroyList(s);
}

void TestStack(void)
{
    int i;
    struct ListNode *s = NULL;

    printf("----- test stack -----\n");
    s = AllocNode(0);
    for (i = 0; i < 10; i++) {
        PushStack(s, i);
    }
    PrintList(s);

    printf("stack top: %d\n", PopStack(s));
    PrintList(s);

    DestroyStack(s);
    DestroyNode(s);
    s = NULL;
}

/******************************************************************************/
int main(void)
{
    TestList();
    TestQueue();
    TestStack();
    return 0;
}
/******************************************************************************/
