/* 二叉树 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree.h>

/*
 * example: AB##C##
 */
void CreateTree(struct BTNode **tree)
{
	char ch;
	scanf("%c", &ch);
	if (ch == '#') {
		*tree = NULL;
		return;
	} else {
		*tree = (struct BTNode *)malloc(sizeof(struct BTNode));
		(*tree)->data = ch;
		CreateTree(&((*tree)->left));
		CreateTree(&((*tree)->right));
	}
}

void PreOrder(struct BTNode *tree)
{
	if (tree == NULL) {
		return;
	}
	printf("%c", tree->data);
	PreOrder(tree->left);
	PreOrder(tree->right);
}

void InOrder(struct BTNode *tree)
{
	if (tree == NULL) {
		return;
	}
	InOrder(tree->left);
	printf("%c", tree->data);
	InOrder(tree->right);
}

void PostOrder(struct BTNode *tree)
{
	if (tree == NULL) {
		return;
	}
	PostOrder(tree->left);
	PostOrder(tree->right);
	printf("%c", tree->data);
}
