/*
 * 练习：二叉树
 * 时间：2020-04-12
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree.h>
#include <stack.h>

/* 测试用例：
AB##C##
ABD##E##C##
ABC##D##EF##G##
*/

typedef char ElementType;

void PrintfPath(struct Stack *s)
{
}

void PrintAllPath(struct BTNode *node, struct Stack *s)
{
    if (node->left == NULL && node->right == NULL) {
        PrintPath(struct Stack *s);
    }
}

int main()
{
	struct BTNode *tree = (struct BTNode *)malloc(sizeof(struct BTNode));
    struct Stack *s = StackCtrate();

	CreateTree(&tree);
	printf("pre order: ");
	PreOrder(tree);
	printf("\nin order: ");
	InOrder(tree);
	printf("\npost order: ");
	PostOrder(tree);
	printf("\n");

	return 0;
}
