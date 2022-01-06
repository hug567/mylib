/*
 * leetcode 103: 二叉树的锯齿形层序遍历 [中等]
 * BFS遍历二叉树，借助队列，注意一下细节：
 *     1）、一维数组作为输出参数；
 *     2）、返回二维数组：
 *     3）、访问一、二维数组元素；
 *     4）、使用循环数组实现FIFO队列；
 *     5）、队列中存储节点的同时存储其深度；
 *     6）、将得到的数组的偶数行翻转
 * 2021-1-6
 */
#include "common.h"
#include "tree.h"

/***** 提交代码 ****************************************************************/
#define MAX_COL_SIZE 130
#define MAX_NODE_NUM 140

int TreeDepth(struct TreeNode *t)
{
    if (t == NULL) {
        return 0;
    }
    int l = TreeDepth(t->left);
    int r = TreeDepth(t->right);
    return (l > r ? l : r) + 1;
}

void ReverseArray(int *arr, int size)
{
    int i, tmp;
    for (i = 0; i < size / 2; i++) {
        tmp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = tmp;
    }
}

struct TreeNode *g_queue[MAX_NODE_NUM] = {NULL};
int g_depth[MAX_NODE_NUM] = {0};
int g_head = 0, g_tail = 0;
int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    int i;
    int depth;
    int **ret = NULL;
    struct TreeNode *t = NULL;

    if (root == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    *returnSize = TreeDepth(root);
    *returnColumnSizes = malloc(*returnSize * sizeof(int));
    ret = malloc(*returnSize * sizeof(int *));
    for (i = 0; i < *returnSize; i++) {
        *(*returnColumnSizes + i) = 0; /* 初始每行元素个数为0 */
        *(ret + i) = malloc(MAX_COL_SIZE * sizeof(int));
    }

    /* BFS遍历二叉树 */
    g_head = 0;
    g_tail = 0;
    g_queue[g_tail] = root; /* 入队 */
    g_depth[g_tail] = 0;
    g_tail++;
    while (g_head != g_tail) {
        t = g_queue[g_head]; /* 出队 */
        depth = g_depth[g_head]; /* 当前节点深度 */
        *(*(ret + depth) + *(*returnColumnSizes + depth)) = t->val;
        (*(*returnColumnSizes + depth))++;  /* 遍历到每行的列数 */
        g_head++;
        g_head %= MAX_NODE_NUM;
        if (t->left != NULL) {
            g_queue[g_tail] = t->left; /* 入队 */
            g_depth[g_tail] = depth + 1;
            g_tail++;
            g_tail %= MAX_NODE_NUM;
        }
        if (t->right != NULL) {
            g_queue[g_tail] = t->right; /* 入队 */
            g_depth[g_tail] = depth + 1;
            g_tail++;
            g_tail %= MAX_NODE_NUM;
        }
    }
    for (i = 0; i < *returnSize; i++) {
        if (i % 2 == 1) {
            ReverseArray(*(ret + i), *(*returnColumnSizes + i));
        }
    }
    return ret;
}

/***** 本地调试 ****************************************************************/
void TestCase1(void)
{
    int i, j;
    int arr[] = {3, 9, 20, -1, -1, 15, 7};
    int size = ARRAY_SIZE(arr);
    struct TreeNode *t = NULL;
    int retSize;
    int *retColSize = NULL;
    int **ret = NULL;

    CreateTreeByLevelArray(&t, arr, size, 0);
    PrintTreeInfo(t);
    ret = zigzagLevelOrder(t, &retSize, &retColSize);
    Log("tree level order array:\n");
    for (i = 0; i < retSize; i++) {
        for (j = 0; j < retColSize[i]; j++) {
            printf("%d ", *(*(ret + i) + j));
        }
        printf("\n");
    }
}

int main(void)
{
    TestCase1();
    return 0;
}
