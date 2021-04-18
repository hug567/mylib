/*
 * 八数码问题：9宫格中有1-8个数字和一个空格子，空格子可与周围数字格子交换，
 *            求移动成12345678x的最短路径，无解输出"unsolvable"
 * 解法：BFS
 * 存储当前棋盘状态，用于判断某一状态是否遍历过：
 *   1、存储字符串，1个状态需要9字节，每个位可能为0-8共9中状态，则一共需要的空间为：
 *      9^9 * 9 = 9^10 = 3486784401 = 3.25G，且判断某一状态是否出现，需比较字符串；
 *   2、将字符串转换为整数，9位整数未超出4字节整形范围，用整形数组记录状态，若已遍历过，
 *      对应下标数组值为1，则需要空间为：876543210 * 4 = 3506172840 = 3.26G；但一种
 *      状态中0-8每个字符只出现一次，造成大量字符浪费。
 * 2021-04-14
 */
#include "common.h"

#define BugOn(a) assert(a)

/* 带头结点的循环双链表实现队列 */
struct ListNode {
    int val;
    struct ListNode *next;
    struct ListNode *pre;
};

struct ListNode g_queue = {
    .val = 0,
    .next = &g_queue,
    .pre = &g_queue,
};

struct ListNode *AllocNode(int val)
{
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = node;
    node->pre = node;
    return node;
}

int IsEmpty(struct ListNode *head)
{
    BugOn(head != NULL);
    if (head->next == head) {
            return 1;
    } else {
        return 0;
    }
}

void EnQueue(struct ListNode *head, int val)
{
    struct ListNode *cur = NULL;
    struct ListNode *node = NULL;

    BugOn(head != NULL);
    cur = head->next;
    node = AllocNode(val);
    while (cur->next != head){
        cur = cur->next;
    }
    node->next = cur->next;
    cur->next->pre = node;
    cur->next = node;
    node->pre = cur;
}

int DeQueue(struct ListNode *head)
{
    int val;
    struct ListNode *node = NULL;

    BugOn(head != NULL);
    if (IsEmpty(head)) {
        return -1;
    }
    node = head->next;
    head->next = node->next;
    node->next->pre = head;
    val = node->val;
    free(node);
    return val;
}

int main(void)
{
    int arr[3][3] = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 },
    };
    PrintArray2((int **)arr, 3, 3);
    //char
    return 0;
}

