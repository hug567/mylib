#include <stdio.h>
#include "test01.h"

static int g_test_var = 0;

void test01_add(void)
{
	g_test_var++;
}

void test01_print(void)
{
	printf("g_test_var = %d\n", g_test_var);
}

void test01_hello(void)
{
	printf("hello test01!\n");
}
