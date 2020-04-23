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
    if (s == NULL || s->len == 0) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * top
 * n1 -> n2 -> ...  ->nk
 */
struct Stack *StackCreate(void)
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
        free(tmp->data);
        free(tmp);
    }
    free(s);
}

/* stack push to top */
void StackPush(struct Stack *s, void *data, size_t size)
{
    struct SNode *tmp = NULL;

    if (s == NULL || data == NULL) {
        return;
    }
    tmp = (struct SNode *)malloc(sizeof(struct SNode));
    tmp->data = malloc(size);
    memcpy(tmp->data, data, size);
    tmp->next = NULL;
    if (StackIsEmpty(s)) {
        s->top = tmp;
    } else {
        tmp->next = s->top;
        s->top = tmp;
    }
    s->len++;
}

/* stack pop from top */
int StackPop(struct Stack *s, void *data, size_t size)
{
    struct SNode *tmp = NULL;

    if (StackIsEmpty(s) || data == NULL) {
        return -1;
    } else {
        tmp = s->top;
        s->top = s->top->next;
        s->len--;
        memcpy(data, tmp->data, size);
        free(tmp->data);
        free(tmp);
        return 0;
    }
}
