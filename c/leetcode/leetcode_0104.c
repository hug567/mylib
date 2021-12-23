/*
 * leetcode 104: 二叉树的最大深度 [简单]
 * 方法：递归计算二叉树深度
 * 2021-12-23
 */
#include "common.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/***** 提交代码 ****************************************************************/
int maxDepth(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }
    int l = maxDepth(root->left);
    int r = maxDepth(root->right);
    return (l > r ? l : r) + 1;
}

/***** 本地调试 ****************************************************************/

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
    int arr[] = {3, 9, -1, -1, 20, 15, -1, -1, 7, -1, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *t = CreateTreeByArray(arr, size);
    DebugLog("tree depth: %d(3)\n", maxDepth(t));
}

int main(void)
{
    TestCase1();
    return 0;
}
