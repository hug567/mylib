/*
 * 练习：链式堆栈
 * 2020-09-16
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StackNode {
    int val;
    struct StackNode *next;
};

struct Stack {
    struct StackNode *top;
    int len;
};

/* 堆栈初始化 */
void InitStack(struct Stack *s)
{
    if (s == NULL) {
        return;
    }
    s->top = NULL;
    s->len = 0;
}

/* 入栈 */
void Push(struct Stack *s, int val)
{
    struct StackNode *sn = NULL;

    sn = (struct StackNode *)malloc(sizeof(struct StackNode));
    sn->val = val;
    sn->next = NULL;
    if (s->len <= 0) {
        s->top = sn;
    } else {
        sn->next = s->top;
        s->top = sn;
    }
    s->len++;
}

/* 出栈 */
int Pop(struct Stack *s)
{
    int val;
    struct StackNode *sn = NULL;

    if (s->len <= 0) {
        return -1;
    }
    sn = s->top;
    s->top = s->top->next;
    s->len--;
    val = sn->val;
    free(sn);
    return val;
}

/* 获取栈顶元素 */
int Top(struct Stack *s)
{
    if (s->len <= 0) {
        return -1;
    }
    return s->top->val;
}

/* 打印堆栈 */
void PrintStack(struct Stack *s)
{
    struct StackNode *sn = NULL;

    printf("stack: ");
    sn = s->top;
    while (sn != NULL) {
        printf("%d ", sn->val);
        sn = sn->next;
    }
    printf("\n");
}

int main(void)
{
    int i;
    struct Stack s;

    InitStack(&s);
    for (i = 0; i < 10; i++) {
        Push(&s, i);
    }
    PrintStack(&s);

    i = Pop(&s);
    printf("pop val: %d\n", i);
    PrintStack(&s);

    return 0;
}
