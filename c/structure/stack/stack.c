/*
 * 练习：栈库函数
 * 时间：2020-04-12
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>

int StackIsEmpty(struct Stack *s)
{
    if (s->len == 0) {
        return 1;
    } else {
        return 0;
    }
}

struct Stack *StackCreate(ElementType)
{
    struct Stack *s = (struct Stack *)malloc(sizeof(struct Stack));
    s->top = NULL;
    s->len = 0;
    return s;
}

void StackDestory(struct Stack *s)
{
    struct SNode *tmp = NULL;

    if (s == NULL) {
        return;
    }
    while (s->top != NULL) {
        tmp = s->top;
        s->top = s->top->next;
        free(tmp);
    }
    free(s);
}

void StackPush(struct Stack *s, void *data)
{
    struct SNode *tmp = NULL;

    if (s == NULL || data == NULL) {
        return;
    }
    tmp = (struct SNode *)malloc(sizeof(struct SNode));
    tmp->data = data;
    tmp->next = NULL;
    if (StackIsEmpty(s)) {
        s->top = tmp;
    } else {
        tmp->next = s->top;
        s->top = tmp;
    }
    s->len++;
}

int StackPop(struct Stack *s, void *data, size_t size)
{
    struct SNode *tmp = NULL;

    if (s == NULL || data == NULL) {
        return -1;
    }
    if (StackIsEmpty(s)) {
        return -1;
    } else {
        tmp = s->top;
        s->top = s->top->next;
        s->len--;
        memcpy(data, tmp->data, size);
        free(tmp);
        return 0;
    }
}
