/*
 * 练习：栈头文件
 * 创建：2020-04-12
 */

#ifndef __STACK_H__
#define __STACK_H__

/* 链栈节点 */
struct SNode {
    void *data;
    struct SNode *next;
};

/* 链栈 */
struct Stack {
    struct SNode *top;
    int len;
};

int StackIsEmpty(struct Stack *s);
struct Stack *StackCreate(void);
void StackDestory(struct Stack *s);
void StackPush(struct Stack *s, void *data);
int StackPop(struct Stack *s, void *data, size_t size);

#endif /* __STACK_H__ */
