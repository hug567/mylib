#include <stdio.h>
#include "test01.h"

void __wrap_test01_print(void)
{
	printf("__wrap_test01_print\n");
}

void __wrapm_test01_print(void)
{
	printf("__wrapm_test01_print\n");
}

int main()
{
	printf("hello makefile!\n");
	test01_print();
	test01_add();
	test01_print();
	test01_add();
	test01_print();
	return 0;
}
