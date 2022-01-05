/*
 * leetcode 102: 二叉树的层序遍历
 * 2021-1-5
 */
#include "common.h"
#include "tree.h"

/***** 提交代码 ****************************************************************/
#define MAX_COL_SIZE 100

int TreeDepth(struct TreeNode *t)
{
    if (t == NULL) {
        return 0;
    }
    int l = TreeDepth(t->left);
    int r = TreeDepth(t->right);
    return (l > r ? l : r) + 1;
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    int i;
    int **ret = NULL;

    *returnSize = TreeDepth(root);
    *returnColumnSizes = malloc(*returnSize * sizeof(int));
    ret = malloc(*returnSize * sizeof(int *));
    for (i = 0; i < *returnSize; i++) {
        *(ret + i) = malloc(MAX_COL_SIZE * sizeof(int));
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
    ret = levelOrder(t, &retSize, &retColSize);
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
