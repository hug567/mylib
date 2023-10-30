/*
 * 测试：container_of定义
 * 时间：2023-10-30
 */
#include <stdio.h>

#define container_of(ptr, type, member) \
	((type *)((char *)(ptr) - (size_t)&((type *)0)->member))

struct student {
	char *name;
	int age;
	int height;
	int weight;
};

int main()
{
	void *ptr, *ptr1, *ptr2, *ptr3;
	struct student stu = {
		.name = "Tom",
		.age = 18,
		.height = 183,
		.weight = 70,
	};

	printf("&stu: 0x%lx\n", (unsigned long)&stu);
	printf("container_of(&stu.age, struct student, age): 0x%lx\n",
		(unsigned long)container_of(&stu.age, struct student, age));

	ptr = &stu;
	ptr1 = container_of(&stu.age, struct student, age);
	ptr2 = container_of(&stu.height, struct student, height);
	ptr3 = container_of(&stu.weight, struct student, weight);

	printf("ptr : 0x%lx\n", (unsigned long)ptr);
	printf("ptr1: 0x%lx\n", (unsigned long)ptr1);
	printf("ptr2: 0x%lx\n", (unsigned long)ptr2);
	printf("ptr3: 0x%lx\n", (unsigned long)ptr3);

	return 0;
}
