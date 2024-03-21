/*
 * 在#define宏中使用#if-#else-#endif
 * 2024-03-21
 */
#include <stdio.h>
#include <stdbool.h>

struct student {
	char *name;
	int age;
	int height;
	bool is_adult;
};

#define DEFINE_STRUCT(_name, _age, _height, _is_adult) \
{ \
	.name = _name, \
	.age = _age, \
	.height = _height, \
	.is_adult = _is_adult, \
}

static int test_macro(void)
{
	int i, size;
	struct student students[] = {
		DEFINE_STRUCT("Tom", 15, 163, false),
		DEFINE_STRUCT("Bob", 19, 172, true),
	};

	size = sizeof(students) / sizeof(struct student);
	for (i = 0; i < size; i++) {
		printf("student name: %s, age: %d, height: %d, is_adult: %d\n",
		       students[i].name, students[i].age, students[i].height,
		       students[i].is_adult);
	}

	return 0;
}

int main(void)
{

	test_macro();

	return 0;
}
