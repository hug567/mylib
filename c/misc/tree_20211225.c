/*
 * 练习：创建二叉树
 * 2021-12-25
 */
#include "common.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int TreeDepth(struct TreeNode *t)
{
    if (t == NULL) {
        return 0;
    }
    int l = TreeDepth(t->left);
    int r = TreeDepth(t->right);
    return (l > r ? l : r) + 1;
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

void InOrder(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    InOrder(t->left);
    printf("%d ", t->val);
    InOrder(t->right);
}

void PostOrder(struct TreeNode *t)
{
    if (t == NULL) {
        return;
    }
    PostOrder(t->left);
    PostOrder(t->right);
    printf("%d ", t->val);
}

void PrintTree(struct TreeNode *t)
{
    Log("----- tree info -----\n");
    Log("tree depth: %d\n", TreeDepth(t));
    Log("pre order: ");
    PreOrder(t);
    printf("\n");
    Log("in order: ");
    InOrder(t);
    printf("\n");
    Log("post order: ");
    PostOrder(t);
    printf("\n");
}

/*
 * 根据树的前序遍历数组创建二叉树
 */
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

/*
 * 根据二叉树的层次遍历数组创建二叉树
 * 父节点：i
 * 左子节点：2*i+1
 * 右子节点：2*i+2
 */
void CreateTreeByArray2(struct TreeNode **t, int *arr, int size, int i)
{
    if (i >= size || arr[i] == -1) {
        *t = NULL;
        return;
    }
    *t = malloc(sizeof(struct TreeNode));
    (*t)->val = arr[i];
    CreateTreeByArray2(&((*t)->left), arr, size, 2 * i + 1);
    CreateTreeByArray2(&((*t)->right), arr, size, 2 * i + 2);
}

/* 根据前序遍历数组创建二叉树 */
void TestCase1(void)
{
    /*
     *   1
     *  / \
     * 2   3
     */
    int arr[] = {1, 2, -1, -1, 3, -1, -1};
    int size = ARRAY_SIZE(arr);
    g_index = 0;
    struct TreeNode *t = CreateTreeByArray(arr, size);
    PrintTree(t);
}

/* 根据层次遍历数组创建二叉树 */
void TestCase2(void)
{
    /*
     *      1
     *    /   \
     *   2     3
     *  /     / \
     * 4     5   6
     */
    int arr[] = {1, 2, 3, 4, -1, 5, 6};
    int size = ARRAY_SIZE(arr);
    struct TreeNode *t = NULL;
    CreateTreeByArray2(&t, arr, size, 0);
    PrintTree(t);
}

int main(void)
{
    TestCase1();
    TestCase2();
    return 0;
}
