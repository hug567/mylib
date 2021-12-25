/*
 * leetcode 100: 相同的树 [简单]
 * 递归判断个节点
 * 2021-12-25
 */
#include "common.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/***** 提交代码 ****************************************************************/
bool isSameTree(struct TreeNode* p, struct TreeNode* q)
{
    if (p == NULL && q == NULL) {
        return true;
    } else if ((p == NULL && q != NULL) || (p != NULL && q == NULL) ||
               (p != NULL && q != NULL && p->val != q->val)) {
        return false;
    } else if (!isSameTree(p->left, q->left)) {
        return false;
    } else if (!isSameTree(p->right, q->right)) {
        return false;
    }
    return true;
}

/***** 本地调试 ****************************************************************/
void PreOrder(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    printf("%d ", t->val);
    PreOrder(t->left);
    PreOrder(t->right);
}

void PrintTree(struct TreeNode *t)
{
    Log("pre order: ");
    PreOrder(t);
    printf("\n");
}

int g_index = 0;
struct TreeNode *CreateTreeByArray(int *arr, int size)
{
    struct TreeNode *t = NULL;
    if (g_index >= size) {
        return NULL;
    } else if (arr[g_index] == -1) {
        g_index++;
        return NULL;
    } else {
        t = malloc(sizeof(struct TreeNode));
        t->val = arr[g_index];
        g_index++;
        t->left = CreateTreeByArray(arr, size);
        t->right = CreateTreeByArray(arr, size);
        return t;
    }
}

void TestCase1(void)
{
    int arr1[] = {1, 2, -1, -1, 3, -1, -1};
    int size1 = ArraySize(arr1);
    g_index = 0;
    struct TreeNode *p = CreateTreeByArray(arr1, size1);
PrintTree(p);
    int arr2[] = {1, 2, -1, -1, 3, -1, -1};
    int size2 = ArraySize(arr2);
    g_index = 0;
    struct TreeNode *q = CreateTreeByArray(arr2, size2);
PrintTree(q);
    Log("is same tree: %d(1)\n", isSameTree(p, q));
}

void TestCase2(void)
{
    int arr1[] = {1, 2, -1, -1, -1};
    int size1 = ArraySize(arr1);
    g_index = 0;
    struct TreeNode *p = CreateTreeByArray(arr1, size1);
    int arr2[] = {1, -1, 2, -1, -1};
    int size2 = ArraySize(arr2);
    g_index = 0;
    struct TreeNode *q = CreateTreeByArray(arr2, size2);
    Log("is same tree: %d(0)\n", isSameTree(p, q));
}

void TestCase3(void)
{
    int arr1[] = {1, 2, -1, -1, 1, -1, -1};
    int size1 = ArraySize(arr1);
    g_index = 0;
    struct TreeNode *p = CreateTreeByArray(arr1, size1);
    int arr2[] = {1, 1, -1, -1, 2, -1, -1};
    int size2 = ArraySize(arr2);
    g_index = 0;
    struct TreeNode *q = CreateTreeByArray(arr2, size2);
    Log("is same tree: %d(0)\n", isSameTree(p, q));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    return 0;
}
