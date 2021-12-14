/*
 * leetcode 98：验证二叉搜索树 [中等]
 * 2021-12-08
 */
#include "common.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/***** 提交代码 ****************************************************************/
bool isValidBST(struct TreeNode* root)
{
    if (root == NULL) {
        return true;
    }
    if (root->left != NULL && root->val <= root->left->val) {
        return false;
    }
    if (root->right != NULL && root->val >= root->right->val) {
        return false;
    }
    if (!isValidBST(root->left)) {
        return false;
    }
    if (!isValidBST(root->right)) {
        return false;
    }
    return true;
}

/***** 本地调试 ****************************************************************/

/* 层次遍历 */
void

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

int main(void)
{
    DebugLog("int min = %d\n", (int)(1U<<31));
    DebugLog("int max = %d\n", (int)(~0U>>1));

    int arr[] = {2, 1, -1, -1, 3, -1, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *t = CreateTreeByArray(arr, size);


    return 0;
}
