/*
 * 练习：二叉查找树
 * 2021-10-25
 */
#include "common.h"

struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *SearchTreeFind(struct TreeNode *root, int key)
{
    if (root == NULL || root->key == key) {
        return root;
    } else if (root->key > key) {
        return SearchTreeFind(root->left, key);
    } else {
        return SearchTreeFind(root->right, key);
    }
}

struct TreeNode *SearchTreeInsert(struct TreeNode *root, struct TreeNode *new)
{
    if (root == NULL) {
        return new;
    } else if (root->key >= new->key) {
        root->left = SearchTreeInsert(root->left, new);
    } else {
        root->right = SearchTreeInsert(root->right, new);
    }
    return root;
}

void InOrder(struct TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    InOrder(root->left);
    printf("%d ", root->key);
    InOrder(root->right);
}

void SearchTreePrint(struct TreeNode *root)
{
    DebugLog("search tree: ");
    InOrder(root);
    printf("\n");
}

struct TreeNode *CreateSearchTreeByArray(int *arr, int size)
{
    int i;
    struct TreeNode *root = NULL, *new = NULL;

    for (i = 0; i < size; i++) {
        new = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        new->key = arr[i];
        new->left = NULL;
        new->right = NULL;
        root = SearchTreeInsert(root, new);
    }
    return root;
}

int main(void)
{
    /*
          3
         / \
        2   5
       /     \
      1       7
     */
    int arr[] = {3, 5, 7, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *root = NULL;

    root = CreateSearchTreeByArray(arr, size);
    SearchTreePrint(root);

    return 0;
}
