/*
 * 题目：leetcode 257: 二叉树的所有路径
 * 难度：简单
 * 技巧：dfs
 * 时间：2020-03-05
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void create_tree(struct TreeNode **tree, int *nums, int len, int idx)
{
	if (idx >= len || nums[idx] == -1) {
		return;
	}

	*tree = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	(*tree)->val = nums[idx];
	(*tree)->left = NULL;
	(*tree)->right = NULL;
	create_tree(&((*tree)->left), nums, len, 2 * idx + 1);
	create_tree(&((*tree)->right), nums, len, 2 * idx + 2);
}

void pre_order(struct TreeNode *tree)
{
	if (tree == NULL) {
		return;
	}

	printf("%d ", tree->val);
	pre_order(tree->left);
	pre_order(tree->right);
}

#define MAX_SIZE 100

void dfs(struct TreeNode *tree, char **strs, int *path, int depth, int *returnSize)
{
	int i;
	if (tree == NULL) {
		return;
	}
	if (tree->left == NULL && tree->right == NULL) {
		path[depth] = tree->val;
		strs[*returnSize] = (char *)malloc(MAX_SIZE);
		memset(strs[*returnSize], '\0', MAX_SIZE);
		for (i = 0; i < depth; i++) {
			sprintf(strs[*returnSize], "%s%d->", strs[*returnSize], path[i]);
		}
		sprintf(strs[*returnSize], "%s%d", strs[*returnSize], path[i]);
		(*returnSize)++;
	} else {
		path[depth] = tree->val;
		depth++;
		dfs(tree->left, strs, path, depth, returnSize);
		dfs(tree->right, strs, path, depth, returnSize);
	}
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** binaryTreePaths(struct TreeNode* root, int* returnSize){
	int path[MAX_SIZE] = {0};
	char **strs = (char **)malloc(MAX_SIZE * sizeof(char *));

	*returnSize = 0;
	if (root == NULL) {
		return NULL;
	}
	dfs(root, strs, path, 0, returnSize);
	return strs;
}

int main()
{
	int i;
	int nums[] = {1, 2, 3, -1, 5};
	int len = sizeof(nums) / sizeof(int);
	struct TreeNode *tree = NULL;
	char **strs = NULL;
	int returnSize = 0;

	create_tree(&tree, nums, len, 0);
	printf("pre order: ");
	pre_order(tree);
	printf("\n");

	strs = binaryTreePaths(tree, &returnSize);
	for (i = 0; i < returnSize; i++) {
		printf("strs[%d] = %s\n", i, strs[i]);
	}

	return 0;
}
