/*
 * 测试带头节点的循环双链表
 * 2024-08-20
 */
#include <stdio.h>
#include <errno.h>
#include "list.h"

#define GENDER_MALE 0
#define GENDER_FEMALE 1

struct student {
	char *name;
	int gender;
	int age;
	struct list_head node;
};

static LIST_HEAD(g_student);

static int init_student_info(struct student *stu, char *name, int gender,
			     int age)
{
	if (stu == NULL) {
		return -EINVAL;
	}
	stu->name = name;
	stu->gender = gender;
	stu->age = age;
	list_init(&stu->node);

	return 0;
}

static int print_student_info(const struct student *stu)
{
	if (stu == NULL) {
		return -EINVAL;
	}
	printf("student name: %s\n", stu->name);
	printf("student gender: %s\n",
	       stu->gender == GENDER_MALE ? "male" : "female");
	printf("student age: %d\n", stu->age);

	return 0;
}

#define STUDENT_SIZE 3
static int test_list_base(void)
{
	int i;
	int stu_size = 0;
	struct student *stu = NULL, *n = NULL;
	struct student all[STUDENT_SIZE] = {0};

	init_student_info(&all[0], "Tom", GENDER_MALE, 18);
	init_student_info(&all[1], "Bob", GENDER_MALE, 19);
	init_student_info(&all[2], "Alice", GENDER_FEMALE, 20);

	for (i = 0; i < STUDENT_SIZE; i++) {
		list_add_tail(&all[i].node, &g_student);
	}

	list_for_each_entry(stu, &g_student, node) {
		print_student_info(stu);
		stu_size++;
	}
	printf("student size: %d\n", stu_size);

	list_for_each_entry_safe(stu, n, &g_student, node) {
		list_del(&stu->node);
	}

	stu_size = 0;
	list_for_each_entry(stu, &g_student, node) {
		stu_size++;
	}
	printf("after list_del, student size: %d\n", stu_size);

	return 0;
}

int main()
{
	test_list_base();

	return 0;
}
