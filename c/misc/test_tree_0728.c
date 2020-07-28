#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
    int data;
    struct Stack *next;
};

struct Tree {
    int data;
    struct Tree *left;
    struct Tree *right;
};

struct Stack *Push(struct Stack *s, int data)
{
    struct Stack *temp = (struct Stack *)malloc(sizeof(struct Stack));
    temp->data = data;
    temp->next = NULL;
    if (s == NULL) {
        s = temp;
    } else {
        temp->next = s;
        s = temp;
    }
    return s;
}

struct Stack *Pop(struct Stack *s, int *data)
{
    struct Stack *temp = NULL;
    if (s == NULL) {
        return NULL;
    }
    temp = s;
    s = s->next;
    if (data != NULL) {
        *data = temp->data;
    }
    free(temp);
    return s;
}

void PrintStack(struct Stack *s)
{
    printf("Stack: ");
    while (s != NULL) {
        printf("%d ", s->data);
        s = s->next;
    }
    printf("\n");
}

static int g_idx = 0;
struct Tree *CreateTreeByArray(int *arr, int size)
{
    struct Tree *t = NULL;
    if (g_idx >= size) {
        return NULL;
    } else if (arr[g_idx] == -1) {
        g_idx++;
    } else {
        t = (struct Tree*)malloc(sizeof(struct Tree));
        t->data = arr[g_idx];
        g_idx++;
        t->left = CreateTreeByArray(arr, size);
        t->right = CreateTreeByArray(arr, size);
    }
    return t;
}

void PreOrder(struct Tree *t)
{
    if (t == NULL) {
        return;
    }
    printf("%d ", t->data);
    PreOrder(t->left);
    PreOrder(t->right);
}

void PrintOnePath(struct Stack *s)
{
    int data;
    struct Stack *temp = NULL;

    while (s != NULL) {
        temp = Push(temp, s->data);
        s = s->next;
    }
    printf("Path: ");
    while (temp != NULL) {
        temp = Pop(temp, &data);
        printf("%d ", data);
    }
    printf("\n");
}

struct Stack *g_s = NULL;
void PrintAllPath(struct Tree *t)
{
    if (t == NULL) {
        return;
    }
    g_s = Push(g_s, t->data);
    if (t->left == NULL && t->right == NULL) {
        PrintOnePath(g_s);
    } else {
        PrintAllPath(t->left);
        g_s = Pop(g_s, NULL);
        PrintAllPath(t->right);
        g_s = Pop(g_s, NULL);
    }
}

int main(void)
{
    int i;
    struct Stack *s = NULL;
    struct Tree *t = NULL;
    int arr[] = {1, 2, -1, -1, 3, -1, -1};

    for (i = 0; i < 10; i++) {
        s = Push(s, i);
    }
    PrintStack(s);
    s = Pop(s, &i);
    PrintStack(s);

    t = CreateTreeByArray(arr, sizeof(arr) / sizeof(arr[0]));
    printf("pre order: ");
    PreOrder(t);
    printf("\n");

    PrintAllPath(t);
    return 0;
}
