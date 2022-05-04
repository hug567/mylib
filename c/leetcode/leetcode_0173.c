/*
 * leetcode 173: 二叉搜索树迭代器 [中等]
 * 思路：先中序遍历二叉树并保存在数组中，再实现迭代器
 * 2022-05-04
 */
#include "common.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/***** 提交代码 ******************************************************************/
typedef struct {
    int *val;
    int count;
    int cur;
} BSTIterator;

int g_count = 0;
void TreeNodeCount(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    g_count++;
    TreeNodeCount(t->left);
    TreeNodeCount(t->right);
}

void InOrder(BSTIterator *bst, struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    InOrder(bst, t->left);
    bst->val[g_count] = t->val;
    g_count++;
    InOrder(bst, t->right);
}

BSTIterator* bSTIteratorCreate(struct TreeNode* root) {
    BSTIterator *bst = NULL;

    bst = malloc(sizeof(BSTIterator));
    bst->cur = 0;
    g_count = 0;
    TreeNodeCount(root);
    bst->count = g_count;
    bst->val = malloc(bst->count * sizeof(int));
    g_count = 0;
    InOrder(bst, root);
    return bst;
}

int bSTIteratorNext(BSTIterator* obj) {
    int val = obj->val[obj->cur];
    obj->cur++;
    return val;
}

bool bSTIteratorHasNext(BSTIterator* obj) {
    return obj->cur < obj->count;
}

void bSTIteratorFree(BSTIterator* obj) {
    free(obj->val);
    free(obj);
}

/***** 本地调试 ******************************************************************/
int g_idx = 0;
struct TreeNode *CreateTreeByArray(int *arr, int size)
{
    struct TreeNode *t = NULL;

    if (g_idx >= size) {
        return NULL;
    } else if (arr[g_idx] == -1) {
        g_idx++;
        return NULL;
    } else {
        t = malloc(sizeof(struct TreeNode));
        t->val = arr[g_idx];
        g_idx++;
        t->left = CreateTreeByArray(arr, size);
        t->right = CreateTreeByArray(arr, size);
        return t;
    }
}

void TestCase1(void)
{
    int arr[] = {7, 3, -1, -1, 15, 9, -1, -1, 20, -1, -1};
    int size = ARRAY_SIZE(arr);
    g_idx = 0;
    struct TreeNode *t = CreateTreeByArray(arr, size);
    BSTIterator *bst = bSTIteratorCreate(t);
    Log("next: %d(3)\n", bSTIteratorNext(bst));
    Log("next: %d(7)\n", bSTIteratorNext(bst));
    Log("has next: %d(1)\n", bSTIteratorHasNext(bst));
    Log("next: %d(9)\n", bSTIteratorNext(bst));
    Log("has next: %d(1)\n", bSTIteratorHasNext(bst));
    Log("next: %d(15)\n", bSTIteratorNext(bst));
    Log("has next: %d(1)\n", bSTIteratorHasNext(bst));
    Log("next: %d(20)\n", bSTIteratorNext(bst));
    Log("has next: %d(0)\n", bSTIteratorHasNext(bst));
    bSTIteratorFree(bst);
}

int main(void)
{
    TestCase1();
    return 0;
}