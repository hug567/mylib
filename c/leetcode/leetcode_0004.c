/*
 * leetcode 4: 寻找两个正序数组的中位数 [困难]
 * 解答：使用带头结点的循环双链表按升序存储两个数组，不需要去重，找出中位数
 * 2021-04-18
 */
#include "common.h"

struct Node;
void PrintList(struct Node *head);

/***** 提交代码 ****************************************************************/

struct Node {
    int val;
    struct Node *next;
    struct Node *pre;
};

struct Node *g_list = NULL;

struct Node *AllocNode(int val)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->val = val;
    node->next = node;
    node->pre = node;
    return node;
}

void FreeNode(struct Node *node)
{
    if (node != NULL) {
        free(node);
    }
}

void InsertToList(struct Node *head, int val)
{
    struct Node *new = NULL;
    struct Node *cur = head->next;

    while (cur != head) {
        if (cur->val > val) {
            break;
        }
        cur = cur->next;
    }
    /* 插入到当前节点前面 */
    new = AllocNode(val);
    cur->pre->next = new;
    new->pre = cur->pre;
    new->next = cur;
    cur->pre = new;
    head->val++; /* 当前链表中节点数 */
}

void DestroyList(struct Node *head)
{
    struct Node *tmp = NULL;
    struct Node *cur = head->next;
    while (cur != head) {
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    head->val = 0;
    head->next = head;
    head->pre = head;
}

int GetNumByIndex(struct Node *head, int idx)
{
    int i = 0;
    struct Node *cur = head->next;

    while (i < idx && cur != head) {
        cur = cur->next;
        i++;
    }
    return cur->val;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    int i;
    double m, n;
    double middle = 0;

    g_list = AllocNode(0);
    for (i = 0; i < nums1Size; i++) {
        InsertToList(g_list, nums1[i]);
    }
    for (i = 0; i < nums2Size; i++) {
        InsertToList(g_list, nums2[i]);
    }

    if (g_list->val % 2 == 1) { /* 总数为奇数的数组的中位数 */
        middle = GetNumByIndex(g_list, g_list->val / 2);
    } else {
        m = GetNumByIndex(g_list, g_list->val / 2 - 1);
        n = GetNumByIndex(g_list, g_list->val / 2);
        middle = (m + n) / 2.0;
    }

    DestroyList(g_list);
    FreeNode(g_list);
    return middle;
}

/***** 本地调试 ****************************************************************/

void PrintList(struct Node *head)
{
    struct Node *cur = head->next;

    DebugLog("List: ");
    while (cur != head) {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

int main(void)
{
    int num1[] = { 1, 3 };
    int numSize1 = sizeof(num1) / sizeof(num1[0]);
    int num2[] = {2};
    int numSize2 = sizeof(num2) / sizeof(num2[0]);
    DebugLog("midian num = %f(2.0)\n", findMedianSortedArrays(num1, numSize1, num2, numSize2));

    int num3[] = { 1, 2 };
    int numSize3 = sizeof(num3) / sizeof(num3[0]);
    int num4[] = { 3, 4 };
    int numSize4 = sizeof(num4) / sizeof(num4[0]);
    DebugLog("midian num = %f(2.5)\n", findMedianSortedArrays(num3, numSize3, num4, numSize4));

    int num5[] = { 1, 1 };
    int numSize5 = sizeof(num5) / sizeof(num5[0]);
    int num6[] = { 1, 2 };
    int numSize6 = sizeof(num6) / sizeof(num6[0]);
    DebugLog("midian num = %f(1.0)\n", findMedianSortedArrays(num5, numSize5, num6, numSize6));

    int *num7 = NULL;
    int numSize7 = 0;
    int num8[] = { 1 };
    int numSize8 = sizeof(num8) / sizeof(num8[0]);
    DebugLog("midian num = %f(1.0)\n", findMedianSortedArrays(num7, numSize7, num8, numSize8));

    int num9[] = { 2 };
    int numSize9 = sizeof(num9) / sizeof(num8[0]);
    int *num10 = NULL;
    int numSize10 = 0;
    DebugLog("midian num = %f(2.0)\n", findMedianSortedArrays(num9, numSize9, num10, numSize10));

    return 0;
}
