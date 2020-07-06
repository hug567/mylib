/*
 * 练习：二叉树, 打印所有路径
 * 技巧：使用栈保存路径，递归遍历二叉树
 * 时间：2020-04-12
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>
#include <stack.h>
#include <tree.h>

/* 测试用例：
AB##C##
ABD##E##C##
ABC##D##EF##G##
*/

typedef char ElementType;

/* 打印一条路径，先翻转栈，再打印 */
void PrintPath(struct Stack *s)
{
	struct SNode *top = NULL;
	struct Stack *tmp = StackCreate();

	if (s == NULL) {
		return;
	}

	/* 翻转栈 */
	top = s->top;
	while (top != NULL) {
		StackPush(tmp, top->data, sizeof(ElementType));
		top = top->next;
	}

	/* 打印路径 */
	top = tmp->top;
	printf("path: ");
	while (top != NULL) {
		printf("%c", *(ElementType *)top->data);
		top = top->next;
		if (top != NULL) {
			printf(" -> ");
		}
	}
	printf("\n");

	StackDestory(tmp);
}

/* 递归打印所有路径 */
void PrintAllPath(struct BTNode *node, struct Stack *s)
{
	if (node == NULL) {
		return;
	}
	StackPush(s, &node->data, sizeof(ElementType));
	if (node->left == NULL && node->right == NULL) {
		PrintPath(s);
	} else {
		PrintAllPath(node->left, s);
		StackPop(s, NULL, 0);
		PrintAllPath(node->right, s);
		StackPop(s, NULL, 0);
	}
}

int main()
{
	//struct BTNode *tree = (struct BTNode *)malloc(sizeof(struct BTNode));
	struct BTNode *tree = NULL;
	struct Stack *s = StackCreate();
	//char *str = "AB##C##";
	char *str = "ABD##E##CF##G##";

	printf("str = %s\n", str);
	//CreateTree(&tree);
	tree = CreateTreeByArray(str);
	printf("tree pre order: ");
	PreOrder(tree);
	printf("\ntree in order: ");
	InOrder(tree);
	printf("\ntree post order: ");
	PostOrder(tree);
	printf("\n");

	PrintAllPath(tree, s);

	StackDestory(s);

	return 0;
}
