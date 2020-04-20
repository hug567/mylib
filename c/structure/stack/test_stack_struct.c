/*
 * 练习：栈库函数
 * 时间：2020-04-12
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>

typedef struct {
    int num;
    char ch;
} ElementType;

static void StackPrint(struct Stack *s)
{
    struct SNode *top = NULL;
    ElementType *data;

    if (StackIsEmpty(s)) {
        return;
    }
    top = s->top;
    printf("stack: \n");
    while (top != NULL) {
        data = (ElementType *)top->data;
        printf("    num = %d, ch = %c\n", data->num, data->ch);
        top = top->next;
    }
}

int main(int argc, char *argv[])
{
    int i;
    ElementType tmp;
    struct Stack *s = NULL;
    printf("hello stack\n");

    /* 创建栈 */
    s = StackCreate();

    /* 入栈 */
    for (i = 0; i < 10; i++) {
        tmp.num = i;
        tmp.ch = i + 'a';
        StackPush(s, &tmp, sizeof(ElementType));
    }

    /* 栈打印 */
    StackPrint(s);

    /* 出栈 */
    if (StackPop(s, &tmp, sizeof(ElementType)) == 0) {
        printf("stack pop, num = %d, ch = %c\n", tmp.num, tmp.ch);
    }

    StackPrint(s);
    tmp.num = 10;
    tmp.ch = 10 + 'a';
    StackPush(s, &tmp, sizeof(ElementType));
    StackPrint(s);

    /* 销毁栈 */
    StackDestory(s);

    return 0;
}
