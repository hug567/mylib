/*
 * leetcode 114: 二叉树展开为链表 [中等]
 * 技巧：二叉树的前序遍历，左子树不为空时，将左子树整个插入到右子树节点下，并将做子树置空
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* 提交代码 ****************************************************************** */
void flatten(struct TreeNode* root){
    struct TreeNode *pre = NULL;
    if (root == NULL) {
        return;
    }
    if (root->left != NULL) {
        pre = root->left;
        while (pre->right != NULL) {
            pre = pre->right;
        }
        pre->right = root->right;
        root->right = root->left;
        root->left = NULL;
    }
    flatten(root->left);
    flatten(root->right);
}

/* 本地调试 ****************************************************************** */
int g_idx = 0;
struct TreeNode *CreateTreeByArray(int *arr, int size)
{
    struct TreeNode *tn = NULL;
    if (g_idx >= size) {
        return NULL;
    } else if (arr[g_idx] < 0) {
        g_idx++;
    } else {
        tn = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        tn->val = arr[g_idx];
        g_idx++;
        tn->left = CreateTreeByArray(arr, size);
        tn->right = CreateTreeByArray(arr, size);
    }
    return tn;
}

void PreOrder(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    printf("%d ", t->val);
    PreOrder(t->left);
    PreOrder(t->right);
}

int main(void)
{
    struct TreeNode *t = NULL;
    int arr[] = {1, 2, 3, -1, -1, 4, -1, -1, 5, -1, 6, -1, -1};

    t = CreateTreeByArray(arr, sizeof(arr) / sizeof(arr[0]));
    printf("tree pre order: ");
    PreOrder(t);
    printf("\n");

    return 0;
}
