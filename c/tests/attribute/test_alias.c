/*
 * learning alias attribute
 * 2023-06-15
 */
#include <stdio.h>

static int add(int a, int b)
{
	return a + b;
}

static int add2(int a, int b) __attribute__((alias("add")));;

static void test_alias_func(void)
{
	printf("[%s:%d] ---------------------------\n", __func__, __LINE__);

	/* call alias function */
	printf("2 + 3 = %d\n", add2(2, 3));
}

int main()
{
	test_alias_func();
	return 0;
}
