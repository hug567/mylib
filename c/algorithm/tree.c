/* 二叉树 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char data;
	struct node *lchild;
	struct node *rchild;
} btnode;

void create_tree(btnode **tree)
{
	char ch;
	scanf("%c", &ch);
	if (ch == '#') {
		*tree = NULL;
		return;
	} else {
		*tree = (btnode *)malloc(sizeof(btnode));
		(*tree)->data = ch;
		create_tree(&((*tree)->lchild));
		create_tree(&((*tree)->rchild));
	}
}

void pre_order(btnode *tree)
{
	if (tree == NULL) {
		return;
	}
	printf("%c", tree->data);
	pre_order(tree->lchild);
	pre_order(tree->rchild);
}

void in_order(btnode *tree)
{
	if (tree == NULL) {
		return;
	}
	pre_order(tree->lchild);
	printf("%c", tree->data);
	pre_order(tree->rchild);
}

void post_order(btnode *tree)
{
	if (tree == NULL) {
		return;
	}
	pre_order(tree->lchild);
	pre_order(tree->rchild);
	printf("%c", tree->data);
}

int main()
{
	btnode *tree = (btnode *)malloc(sizeof(btnode));

	printf("input tree: ");
	create_tree(&tree);
	printf("pre order: ");
	pre_order(tree);
	printf("\nin order: ");
	in_order(tree);
	printf("\npost order: ");
	post_order(tree);
	printf("\n");

	return 0;
}
