/*
 * 练习：栈库函数
 * 时间：2020-04-12
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>

typedef int ElementType;

static void StackPrint(struct Stack *s)
{
    ElementType *data = NULL;
    struct SNode *top = NULL;

    if (StackIsEmpty(s)) {
        return;
    }
    top = s->top;
    printf("stack: ");
    while (top != NULL) {
        data = top->data;
        printf("%d ", *data);
        top = top->next;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int i;
    ElementType *tmp = NULL;
    ElementType data;
    struct Stack *s = NULL;
    printf("hello stack\n");

    s = StackCreate();
    for (i = 0; i < 10; i++) {
        tmp = (int *)malloc(sizeof(int));
        *tmp = i;
        StackPush(s, tmp);
    }
    StackPrint(s);
    if (StackPop(s, &data, sizeof(ElementType)) == 0) {
        printf("stack pop data = %d\n", data);
    }
    StackPrint(s);
    tmp = (int *)malloc(sizeof(int));
    *tmp = 100;
    StackPush(s, tmp);
    StackPrint(s);
    return 0;
}
