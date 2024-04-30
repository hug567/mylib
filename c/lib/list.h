/*
 * 带头节点的循环双链表
 * 2024-04-30
 */

#define container_of(ptr, type, member) \
	(type *)((uintptr_t)(ptr) - (uintptr_t)(&((type *)0)->member))
