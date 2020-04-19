/*
 * 练习：栈库函数
 * 时间：2020-04-12
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>

typedef struct {
    int a;
    char b;
} ElementType;

static void StackPrint(struct Stack *s)
{
    struct SNode *top = NULL;

    if (StackIsEmpty(s)) {
        return;
    }
    top = s->top;
    printf("stack: ");
    while (top != NULL) {
        printf("%c ", *(ElementType *)top->data);
        top = top->next;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int i;
    ElementType tmp;
    struct Stack *s = NULL;
    printf("hello stack\n");

    s = StackCreate();
    for (i = 0 + 'a'; i < 10 + 'a'; i++) {
        StackPush(s, &i, sizeof(ElementType));
    }
    StackPrint(s);
    if (StackPop(s, &tmp, sizeof(ElementType)) == 0) {
        printf("stack pop data = %c\n", tmp);
    }
    StackPrint(s);
    tmp = 10 + 'a';
    StackPush(s, &tmp, sizeof(ElementType));
    StackPrint(s);
    return 0;
}
