/*
 * leetcode 116: 填充每一个节点的下一个右侧节点指针
 * 思路：BFS层次遍历二叉树，若当前节点与前一个节点在同一层，前一节点的next指向当前节点
 * 2021-1-7
 */
#include "common.h"

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

/***** 提交代码 ****************************************************************/
#define MAX_QUEUE_SIZE 2100
struct Node *g_queue[MAX_QUEUE_SIZE];
int g_depth[MAX_QUEUE_SIZE];
int g_head, g_tail;

struct Node* connect(struct Node* root)
{
    struct Node *n = NULL, *pre_n = NULL;
    int depth, pre_depth = -1;

    if (root == NULL) {
        return root;
    }

    g_head = 0;
    g_tail = 0;
    g_queue[g_tail] = root;
    g_depth[g_tail] = 0;
    g_tail++;
    while (g_head != g_tail) {
        n = g_queue[g_head];
        depth = g_depth[g_head];
        g_head++;
        g_head %= MAX_QUEUE_SIZE;
        if (pre_n != NULL && pre_depth == depth) {
            pre_n->next = n;
        }
        pre_n = n;
        pre_depth = depth;
        if (n->left != NULL) {
            g_queue[g_tail] = n->left;
            g_depth[g_tail] = depth + 1;
            g_tail++;
            g_tail %= MAX_QUEUE_SIZE;
        }
        if (n->right != NULL) {
            g_queue[g_tail] = n->right;
            g_depth[g_tail] = depth + 1;
            g_tail++;
            g_tail %= MAX_QUEUE_SIZE;
        }
    }

    return root;
}

/***** 本地调试 ****************************************************************/

void CreateTreeByLevelArr(struct Node **n, int *arr, int size, int index)
{
    if (index >= size || arr[index] == -1) {
        *n = NULL;
        return;
    }
    *n = malloc(sizeof(struct Node));
    (*n)->val = arr[index];
    (*n)->next = NULL;
    CreateTreeByLevelArr(&((*n)->left), arr, size, 2 * index + 1);
    CreateTreeByLevelArr(&((*n)->right), arr, size, 2 * index + 2);
}

void PreOrder(struct Node *n)
{
    if (n == NULL) {
        return;
    }
    printf("%d", n->val);
    if (n->next != NULL) {
        printf("(%d) ", n->next->val);
    } else {
        printf("(N) ");
    }
    PreOrder(n->left);
    PreOrder(n->right);
}

void PrintTree(struct Node *n)
{
    Log("pre order: ");
    PreOrder(n);
    printf("\n");
}

void TestCase1(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = ARRAY_SIZE(arr);
    struct Node *n = NULL;
    CreateTreeByLevelArr(&n, arr, size, 0);
    PrintTree(n);
    n = connect(n);
    PrintTree(n);
}

int main(void)
{
    TestCase1();
    return 0;
}
