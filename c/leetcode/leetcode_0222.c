/*
 * leetcode 222: 完全二叉树节点个数 [中等]
 * 思路：前序遍历一遍二叉树，计算出节点个数
 * 注意：leetcode全局变量每次使用前均需重新初始化
 * 2022-04-17
 */
#include "common.h"

struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };

/***** 提交代码 ******************************************************************/
int g_count = 0;

void PreOrder(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    g_count++;
    PreOrder(t->left);
    PreOrder(t->right);
}

int countNodes(struct TreeNode* root){
    g_count = 0;
    PreOrder(root);
    return g_count;
}

/***** 本地调试 ******************************************************************/
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
    int arr[] = { 1, 2, 4, -1, -1, 5, -1, -1, 3, 6, -1, -1 };
    int size = ARRAY_SIZE(arr);
    g_index = 0;
    struct TreeNode *t = CreateTreeByArray(arr, size);
    Log("node count: %d(6)\n", countNodes(t));
}

int main(void)
{
    TestCase1();
    return 0;
}