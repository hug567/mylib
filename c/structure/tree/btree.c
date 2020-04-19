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

void TestPrintStack(struct Stack *s)
{
}

void TestStackChar(void)
{
    int i;
    char *ch = NULL;
    struct Stack *s = NULL;

    s = StackCreate();
    for (i = 0; i < 26; i++) {
        ch = (char *)
    }
}

int main()
{
	struct BTNode *tree = (struct BTNode *)malloc(sizeof(struct BTNode));

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
